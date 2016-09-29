/*======================================================================
 
---------------------------DATALOG DECLARATIONS-------------------------
 
======================================================================*/

// Include libraries and files
#pragma once
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the datalog class
class Datalog
{
    // Establish friend classes
    friend class Parser;
    friend class Database;

    private:
        // Data Members
        vector<Predicate> mySchemes;
        vector<Predicate> myFacts;
        vector<Rule> myRules;
        vector<Predicate> myQueries;
        vector<string> myDomain;
    
    public:
        // Constructor
        Datalog();
    
        // Member Functions
        bool domainSearch(string);
        void addSchemes(Predicate);
        void addFacts(Predicate);
        void addRules(Rule);
        void addQueries(Predicate);
        void addDomain(string);
        string toString();
        void clear();
        void stringValue(vector<Predicate>, vector<string>&);
    
        // Destructor
        virtual ~Datalog();
};

//======================================================================