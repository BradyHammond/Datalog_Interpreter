/*======================================================================
 
--------------------------DATABASE DECLARATIONS-------------------------
 
======================================================================*/

// Include libraries and files
#pragma once
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "Parser.h"
#include "Relation.h"
#include "Datalog.h"
#include "Graph.h"
#include "Node.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the database class
class Database
{
    private:
        // Data Members
        Datalog program;
        map<string, Relation> relations;
        vector<string> values;
        Graph graph;
    
    public:
        // Constructor
        Database();
    
        // Member Functions
        void evaluateSchemes();
        void evaluateFacts();
        string evaluateRules(vector<Rule>&);
        string evaluateQueries();
        void loadDatalog(Datalog);
        void addScheme(int);
        void addFact(int);
        Relation select(Relation, int);
        Relation project(Relation, int);
        Relation rename(Relation, int);
        bool isString(char);
        string toString();
        Relation alternativeSelect(Relation, vector<Parameter>);
        Relation alternativeProject(Relation, vector<Parameter>);
        Relation projectRules(Relation, vector<Parameter>);
        Relation alternativeRename(Relation, vector<Parameter>);
        int countTuples();
        string printVector();
        void print(string);
        string createGraph();
        bool repeatAgain(vector<Rule>);
        string evaluateRulesFromGraph();
    
        // Destructor
        virtual ~Database();
};

//======================================================================