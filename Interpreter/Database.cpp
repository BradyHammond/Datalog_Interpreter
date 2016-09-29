/*======================================================================
 
--------------------------DATABASE DEFINITIONS--------------------------
 
======================================================================*/

// Include files
#include "Database.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the database constructor
Database::Database(){}

//======================================================================

// Define the is string function
bool Database::isString(char value)
{
    if(value == '\'')
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

//======================================================================

// Define the load datalog program
void Database::loadDatalog(Datalog program)
{
    this->program = program;
}

//======================================================================

// Define the evaluate schemes function
void Database::evaluateSchemes()
{
    for(int i = 0; i < program.mySchemes.size(); ++i)
    {
        addScheme(i);
    }
}


//======================================================================

// Define the add scheme function
void Database::addScheme(int index)
{
    string name = program.mySchemes[index].name;
    Relation relation = Relation(name);
    
        
    for(int i = 0; i < program.mySchemes[index].parameter.size(); ++i)
    {
        relation.schemes_list.push_back(program.mySchemes[index].parameter[i].parameter);
    }
    relations.insert(pair<string, Relation> (name, relation));
}

//======================================================================

// Define the evaulate facts function
void Database::evaluateFacts()
{    
    for(int i = 0; i < program.myFacts.size(); ++i)
    {
        addFact(i);
    }
    
}

//======================================================================

// Define the add fact function
void Database::addFact(int index)
{    
    string name = program.myFacts[index].name;
    Tuple tuple;
        
    for(int i = 0; i < program.myFacts[index].parameter.size(); ++i)
    {
        tuple.push_back(program.myFacts[index].parameter[i].parameter);
    }
    
    relations.at(name).tuples.insert(tuple);
}

//======================================================================

// Define the select function
Relation Database::select(Relation relation, int index)
{
    vector<string> variables; 
    
    for(int i = 0; i < program.myQueries[index].parameter.size(); ++i)
    {
        string parameter = program.myQueries[index].parameter[i].parameter;
        if(isString(program.myQueries[index].parameter[i].parameter[0]) == true)
        {
            relation = relation.select(i, parameter);
            variables.push_back(parameter);
        }
        
        else
        {
            bool duplicate_check = false;
            int duplicate_index = 0;
            
            for(int j = 0; j < variables.size(); ++j)
            {
                if(variables[j] == parameter)
                {
                    duplicate_index = j;
                    duplicate_check = true;
                }
            }
            
            if(duplicate_check == true)
            {
                relation = relation.selectCompare(duplicate_index, i);
            }
            
            else
            {
                variables.push_back(parameter);
            }
        }
    }
        
    return relation;
}

//======================================================================

// Define the project function
Relation Database::project(Relation relation, int index)
{
    vector<int> indices;
    vector<string> variables;
    
    for(int i = 0; i < program.myQueries[index].parameter.size(); ++i)
    {
        string parameter = program.myQueries[index].parameter[i].parameter;
        bool nonterminal_check = !isString(program.myQueries[index].parameter[i].parameter[0]);
        bool duplicate_check = false;
        
        for(int j = 0; j < variables.size(); ++j)
        {
            if(variables[j] == parameter)
            {
                duplicate_check = true;
            }
        }
        
        if(nonterminal_check == true && duplicate_check == false)
        {
            indices.push_back(i);
            variables.push_back(parameter);
        }
    }
    
    relation = relation.project(indices);
    
    return relation;
}

//======================================================================

Relation Database::rename(Relation relation, int index)
{
    vector<string> variables;
    
    for(int i = 0; i < program.myQueries[index].parameter.size(); ++i)
    {
        string parameter = program.myQueries[index].parameter[i].parameter;
        bool nonterminal_check = !isString(program.myQueries[index].parameter[i].parameter[0]);
        bool duplicate_check = false;
        
        for(int j = 0; j < variables.size(); ++j)
        {
            if(variables[j] == parameter)
            {
                duplicate_check = true;
            }
        }
        
        if(nonterminal_check == true && duplicate_check == false)
        {
            variables.push_back(parameter);
        }
    }
    
    relation = relation.rename(variables);
    
    return relation;
}

//======================================================================

// Define the alternative select function
Relation Database::alternativeSelect(Relation relation, vector<Parameter> parameters)
{
    vector<string> attributes;
    
    for(int i = 0; i < parameters.size(); ++i)
    {
        string parameter = parameters[i].parameter;
        if(parameter[0] == '\'')
        {
            relation = relation.select(i, parameter);
        }
        
        else
        {
            bool duplicate_check = false;
            int duplicate_index = 0;
            
            for(int j = 0; j < attributes.size(); ++j)
            {
                if(attributes[j] == parameter)
                {
                    duplicate_index = j;
                    duplicate_check = true;
                }
            }
            
            if(duplicate_check == true)
            {
                relation = relation.selectCompare(duplicate_index, i);
            }
            
            else
            {
                attributes.push_back(parameter);
            }
        }
    }
    
    return relation;
}

//======================================================================

// Define the alternative project function
Relation Database::alternativeProject(Relation relation, vector<Parameter> parameters)
{
    vector<int> indices;
    vector<string> attributes;
    
    for(int i = 0; i < parameters.size(); ++i)
    {
        string parameter = parameters[i].parameter;
        bool nonterminal_check = !isString(parameters[i].parameter[0]);
        bool duplicate_check = false;
        
        for(int j = 0; j < attributes.size(); ++j)
        {
            if(attributes[j] == parameter)
            {
                duplicate_check = true;
            }
        }
        
        if(nonterminal_check == true && duplicate_check == false)
        {
            indices.push_back(i);
            attributes.push_back(parameter);
        }
    }
    
    relation = relation.project(indices);
    
    return relation;
}

//======================================================================

// Define the project rules function
Relation Database::projectRules(Relation relation, vector<Parameter> parameter_list)
{
    vector<int> indices;
    
    for(auto parameters : parameter_list)
    {
        for(int i = 0; i < relation.schemes_list.size(); ++i)
        {
            if(parameters.parameter == relation.schemes_list[i])
            {
                indices.push_back(i);
            }
        }
    }
    
    relation = relation.project(indices);
    
    return relation;
}

//======================================================================

// Define alternative rename function
Relation Database::alternativeRename(Relation relation, vector<Parameter> parameters)
{
    vector<string> attributes;
    
    for(int i = 0; i < parameters.size(); ++i)
    {
        string parameter = parameters[i].parameter;
        bool nonterminal_check = !isString(parameter[0]);
        bool duplicate_check = false;
        
        for(int j = 0; j < attributes.size(); ++j)
        {
            if(attributes[j] == parameter)
            {
                duplicate_check = true;
            }
        }
        
        if(nonterminal_check == true && duplicate_check == false)
        {
            attributes.push_back(parameter);
        }
    }
    
    relation = relation.rename(attributes);
    
    return relation;
}

//======================================================================

// Define the count tuples function
int Database::countTuples()
{
    int count = 0;
    for(auto relate : relations)
    {
        for(auto tuple : relate.second.tuples)
        {
            count++;
        }
    }
    return count;
}

//======================================================================

// Define the evaluate rules function
string Database::evaluateRules(vector<Rule> &rules)
{
    stringstream ss;
    int start_count = 0;
    int end_count = 0;
    int total_iterations = 0;
    
    bool repeat = true;
    if(rules.size() == 1)
    {
        repeat = repeatAgain(rules);
    }
    
    do
    {
        total_iterations++;
        start_count = countTuples();
        
        for(auto rule : rules)
        {
            Relation result = Relation("");
            vector<Relation> temporary_relation;
            
            for(auto predicate : rule.rule_body)
            {
                string name = predicate.name;
                Relation r_temporary = relations.at(name);
                r_temporary = alternativeSelect(r_temporary, predicate.parameter);
                r_temporary = alternativeProject(r_temporary, predicate.parameter);
                r_temporary = alternativeRename(r_temporary, predicate.parameter);
                temporary_relation.push_back(r_temporary);
            }
            
            result = temporary_relation[0];

            if(temporary_relation.size() > 1)
            {
                for(int i = 1; i < temporary_relation.size(); ++i)
                {
                    Relation relation_II = temporary_relation[i];
                    result = result.join(relation_II);
                }
            }
            
            result = projectRules(result, rule.rule_head[0].parameter);
            result = alternativeRename(result, rule.rule_head[0].parameter);
            
            ss << rule.toString();
            ss << relations.at(rule.rule_head[0].name).makeUnion(result);
        }
        
        end_count = countTuples();
    }

    while((end_count - start_count) > 0 && repeat == true);
    
    return ss.str();
}


//======================================================================

// Define the evaluate queries function
string Database::evaluateQueries()
{
    stringstream ss;
    
    for(int i = 0; i < program.myQueries.size(); ++i)
    {
        string relation_name = program.myQueries[i].name;
        ss << program.myQueries[i].toString() << "?";
        
        Relation temporary_relation = relations.at(relation_name);
        Relation relation_select = select(temporary_relation, i);
        Relation relation_project = project(relation_select, i);
        Relation relation_rename = rename(relation_project, i);
        
        if(relation_select.tuples.size() > 0)
        {
            ss << " Yes(" << relation_select.tuples.size() << ")\n";
            
            ss << "select\n";
            ss << relation_select.toString();
            
            ss << "project\n";
            ss << relation_project.toString();
            
            ss << "rename\n";
            ss << relation_rename.toString();
            
        }
        else
        {
            ss << " No\n";
        }
        ss << endl;
    }
    
    return ss.str();
}

//======================================================================

// Define the to string function
string Database::toString()
{
    stringstream ss;
    
    for(auto evaluate : relations)
    {
        string name = evaluate.first;
        ss << name << endl;
        
        Relation relation = Relation(name);
        for(auto tuple : relation.tuples)
        {
            for(int i = 0; i < relation.schemes_list.size(); ++i)
            {
                ss << "  " << relation.schemes_list[i] << "=" << tuple.at(i);
            }
            
            ss << endl;
        }
        
        ss << endl;
    }
    
    return ss.str();
}

//======================================================================

// Define the print vector function
string Database::printVector()
{
    stringstream ss;
    string name_copy = "b";
    string name = "a";
    
    vector<string> temporary_scheme;
    program.stringValue(program.mySchemes, temporary_scheme);
    sort(temporary_scheme.begin(), temporary_scheme.end());
	    
    for(int i = 0; i < temporary_scheme.size(); ++i)
    {
        name = temporary_scheme[i];
        
        if(name_copy != name)
        {
            Relation relation = relations.at(name);
            ss << name << endl;
            ss << relation.toString();
            ss << endl;
        }
        
        name_copy = name;
        
    }
   
    return ss.str();
}

//======================================================================

// Define the print function
void Database::print(string output_file)
{
    string output = "";
    ofstream file(output_file);
    
    output = "Scheme Evaluation\n\n";
    evaluateSchemes();
    
    output += "Fact Evaluation\n\n";
    evaluateFacts();
    output += printVector();
    
    output += "Rule Evaluation\n\n";
    output += createGraph();
    output += evaluateRulesFromGraph();
    output += "Rule Evaluation Complete\n\n";
    output += printVector();
    
    output += "Query Evaluation\n\n";
    output += evaluateQueries();
    
    file << output;
    file.close();
}

//======================================================================

// Define the create graph function
string Database::createGraph()
{
    stringstream ss;
    
    graph = Graph(program.myRules);
    ss << graph.printGraph();
    ss << graph.printReverseGraph();
    ss << graph.printScc();
    
    return ss.str();
}

//======================================================================

// Define the repeat again function
bool Database::repeatAgain(vector<Rule> rules)
{
    bool repeat = false;
    string head = rules[0].rule_head[0].name;
    
    for(auto body : rules[0].rule_body)
    {
        if(head == body.name)
        {
            repeat = true;
        }
    }
    
    return repeat;
}

//======================================================================

// Define the evaluate rules from graph function
string Database::evaluateRulesFromGraph()
{
    stringstream ss;
    
    vector<int> postorder_numbers = graph.getHighestToLowestPON();
    map<int, set<int>> strongly_connected_components = graph.scc;
    
    for(auto index : postorder_numbers)
    {
        vector<Rule> evaluate;
        int count = 0;
        
        if(strongly_connected_components.at(index).size() > 0)
        {
            ss << "SCC:";
            for(auto rule_number : strongly_connected_components.at(index))
            {
                count++;
                ss << " R" << rule_number;
                evaluate.push_back(program.myRules[rule_number]);

                if(count == strongly_connected_components.at(index).size())
                {
                    ss << endl;
                }
            }
        }
        
        ss << evaluateRules(evaluate);
        
        if(strongly_connected_components.at(index).size() > 0)
        {
            ss << endl;
        }
    }
    
    return ss.str();
}

//======================================================================

// Define the database destructor
Database::~Database(){}

//======================================================================
