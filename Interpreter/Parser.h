/*======================================================================
 
---------------------------PARSER DECLARATIONS--------------------------
 
======================================================================*/

// Include libraries and files
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Scanner.h"
#include "Datalog.h"
#include "Predicate.h"
#include "Rule.h"

// Setup namespace
using namespace std;

//======================================================================

class Parser
{
    // Establish friend classes
    friend class Database;

    private:
        // Data Members
        Scanner scanner;
        Datalog datalog;
        Predicate predicate_string;
        Rule rule_string;
        bool rule_check;
        bool read_rule_head;
    
    public:
        // Constructor
        Parser();

        // Data Member
        static bool error_flag;
    
        // Member Functions
        void checkFile(string, string, char);
        bool match(TokenType);
        string passIn(TokenType);
        void parseDatalogProgram();
        bool isSchemesEmpty();
        bool isQueriesEmpty();
        void matchScheme();
        void matchFact();
        void matchRule();
        void matchQueries();
        void parseScheme();
        void parseSchemeList();
        void parseFact();
        void parseFactList();
        void parseRule();
        void parseRuleList();
        void parseQueries();
        void parseQueriesList();
        string parsePredicate();
        string parsePredicateList();
        string parseParameter();
        string parseParameterList();;
        void print(string);
        Datalog getDatalog();
        void readRule(string);
        void subParseParameter(string);
    
        // Destructor
        virtual ~Parser();
};

//======================================================================