/*======================================================================
 
---------------------------PARSER DEFINITIONS---------------------------
 
======================================================================*/

// Include libraries and files
#include <stdio.h>
#include "Parser.h"

// Setup namespace
using namespace std;

//======================================================================

// Define variables
bool Parser::error_flag = false;

//======================================================================

// Define the parser constructor
Parser::Parser()
{
    predicate_string = Predicate("");
    rule_string = Rule("");
    rule_check = false;
    read_rule_head = false;
}

//======================================================================

// Define the get datalog function
Datalog Parser::getDatalog()
{
    return datalog;
}

//======================================================================

// Define the check file function
void Parser::checkFile(string filename, string output_file, char current_character)
{
    scanner.getFile(filename, output_file, current_character);
}

//======================================================================

// Define the match function
bool Parser::match(TokenType type)
{
    if(scanner.getType() == type)
    {
        scanner.nextToken();
        return true;
    }
    
    else
    {
        error_flag = true;
        return false;
    }
}

//======================================================================

// Define the pass in function
string Parser::passIn(TokenType type)
{
    string passin = "";

    if(scanner.getType() == type)
    {
        passin += scanner.token_list[scanner.current_token].getID();
        scanner.nextToken();
    }
    
    else
    {
        error_flag = true;
    }
    
    return passin;
}

//======================================================================

// Define the is schemes empty function
bool Parser::isSchemesEmpty()
{
    if(datalog.mySchemes.size() == 0)
    {
        return true;
    }
    
    return false;
}


//======================================================================

// Define the is queries empty function
bool Parser::isQueriesEmpty()
{
    if(datalog.myQueries.size() == 0)
    {
        return true;
    }
    
    return false;
}

//======================================================================

// Define the match scheme function
void Parser::matchScheme()
{
    match(SCHEMES);
    match(COLON);
    
    if(error_flag == true)
    {
        return;
    }
    
    parseSchemeList();
    if(isSchemesEmpty() == true)
    {
        error_flag = true;
    }
}

//======================================================================

// Define the match fact function
void Parser::matchFact()
{
    match(FACTS);
    match(COLON);
    
    if(error_flag == true)
    {
        return;
    }
    
    parseFactList();
}

//======================================================================

// Define the match rule function
void Parser::matchRule()
{
    match(RULES);
    match(COLON);
    
    if(error_flag == true)
    {
        return;
    }
    
    parseRuleList();
}

//======================================================================

// Define the match query function
void Parser::matchQueries()
{
    match(QUERIES);
    match(COLON);
    
    if(error_flag == true)
    {
        return;
    }
    
    parseQueriesList();
    
    if(isQueriesEmpty() == true)
    {
        error_flag = true;
    }
}

//======================================================================

// Define the parse datalog program
void Parser::parseDatalogProgram()
{
    try
    {
        matchScheme();
        if(error_flag == true)
        {
            return;
        }

        matchFact();
        if(error_flag == true)
        {
            return;
        }

        matchRule();
        if(error_flag == true)
        {
            return;
        }
        
        matchQueries();
        if(error_flag == true)
        {
            return;
        }
        
        if(match(ENDOF) == true)
        {
            return;
        }
        
        else
        {
            parseDatalogProgram();
        }
        
    }
    
    catch (Token invalidToken)
    {
        error_flag = true;
    }
}

//======================================================================

// Define the parse scheme function
void Parser::parseScheme()
{
    parsePredicate();
    datalog.addSchemes(predicate_string);
}

//======================================================================

// Define the parse scheme list function
void Parser::parseSchemeList()
{
    if(scanner.getType() == ID)
    {
        parseScheme();
        
        if(error_flag == true)
        {
            return;
        }
        
        parseSchemeList();
    }
}

//======================================================================

// Define the parse fact function
void Parser::parseFact()
{
    parsePredicate();
    
    if(error_flag == true)
    {
        return;
    }
    
    match(PERIOD);
    datalog.addFacts(predicate_string);
}

//======================================================================

// Define the parse fact list function
void Parser::parseFactList()
{
    if(scanner.getType() == ID)
    {
        parseFact();
        
        if(error_flag == true)
        {
            return;
        }
        
        parseFactList();
    }
}

//======================================================================

// Define the parse rule function
void Parser::parseRule()
{
    rule_check = true;
    read_rule_head = false;
    parsePredicate();
    read_rule_head = true;
    passIn(COLON_DASH);
    parsePredicate();
    parsePredicateList();
    
    if(error_flag == true)
    {
        return;
    }
    
    match(PERIOD);
    rule_check = false;
    datalog.addRules(rule_string);
}

//======================================================================

// Define the parse rule list function
void Parser::parseRuleList()
{
    if(scanner.getType() == ID)
    {
        parseRule();
        
        if(error_flag == true)
        {
            return;
        }
        
        parseRuleList();
    }
}

//======================================================================

// Define the read rule function
void Parser::readRule(string predicate)
{
    if(read_rule_head == false) 
    { 
        rule_string = Rule(predicate);
        rule_string.rule_head.push_back(Predicate(rule_string.name));
    }
    
    else if (read_rule_head == true)
    {
        Rule temporary = Rule(predicate);
        rule_string.rule_body.push_back(Predicate(temporary.name));
    }
}

//======================================================================

// Define the sub parse parameter function
void Parser::subParseParameter(string parameter)
{
    if(read_rule_head == false && rule_check == true)
    {

        rule_string.rule_head[0].parameter.push_back(parameter);
    }
    
    else if (read_rule_head == true && rule_check == true)
    {
        int index = -1;
        
        for(int i = 0; i < rule_string.rule_body.size(); ++i)
        {
            index = rule_string.findIndex(rule_string.rule_body[i].name, rule_string.rule_body);
        }
        
        rule_string.rule_body.at(index).parameter.push_back(parameter);
    }
}

//======================================================================

// Define the parse queries function
void Parser::parseQueries()
{
    parsePredicate();
    
    if(error_flag == true)
    {
        return;
    }
    
    match(Q_MARK);
    
    datalog.addQueries(predicate_string);
}

//======================================================================

// Define the parse queries list function
void Parser::parseQueriesList()
{
    if(scanner.getType() == ID)
    {
        parseQueries();
        
        if(error_flag == true)
        {
            return;
        }
        
        parseQueriesList();
    }
}

//======================================================================

// Define the parse predicate function
string Parser::parsePredicate()
{
    string predicate = "";

    predicate += passIn(ID);
    predicate_string = Predicate(predicate);
    
    if(rule_check == true)
    {
        readRule(predicate);
    }
    
    if(error_flag == true)
    {
        return "";
    }
    
    predicate += passIn(LEFT_PAREN);

    if(error_flag == true)
    {
        return "";
    }
    
    predicate += parseParameter();

    if(error_flag == true)
    {
        return "";
    }
    
    predicate += parseParameterList();

    if(error_flag == true)
    {
        return "";
    }
    
    predicate += passIn(RIGHT_PAREN);
    
    return predicate;
}

//======================================================================

// Define the parse predicate list function
string Parser::parsePredicateList()
{
    string pred = "";
    if(scanner.getType() == COMMA)
    {
        pred += passIn(COMMA);
        pred += parsePredicate();
        pred += parsePredicateList();
    }
    return pred;
}

//======================================================================

// Define the parse parameter function
string Parser::parseParameter()
{
    string parameter = "";
    if(scanner.getType() == ID)
    {
        parameter += passIn(ID);
        predicate_string.parameter.push_back(Parameter(parameter));
        subParseParameter(parameter);
    }
    else if(scanner.getType() == STRING)
    {
        parameter += passIn(STRING);
        predicate_string.parameter.push_back(Parameter(parameter));
        
        if (read_rule_head == true && rule_check == true)
        {
            int index = -1;
            
            for(int i = 0; i < rule_string.rule_body.size(); ++i)
            {
                index = rule_string.findIndex(rule_string.rule_body[i].name, rule_string.rule_body);
            }
            rule_string.rule_body.at(index).parameter.push_back(parameter);
        }
        
        datalog.addDomain(parameter);
    }
    
    else
    {
        error_flag = true;
        return "";
    }
    
    return parameter;
}

//======================================================================

// Define the parse parameter list function
string Parser::parseParameterList()
{
    string parameter = "";
    if(scanner.getType() == COMMA)
    {
        parameter += passIn(COMMA);
        parameter += parseParameter();
        
        if(error_flag == true)
        {
            return "";
        }
        
        parameter += parseParameterList();
    }
    
    return parameter;
}

//======================================================================

// Define the print function
void Parser::print(string output_file)
{
    string output;
    ofstream fout(output_file);

    if(error_flag == false)
    {
        output = "Success!\n";
        output += datalog.toString();
        fout << output;
    }
    
    else
    {
        output = "Failure!\n";
        output += "  " + scanner.getToken();
        fout << output;
    }
    
    fout.close();
}

//======================================================================

// Define the parser destructor
Parser::~Parser() {}

//======================================================================