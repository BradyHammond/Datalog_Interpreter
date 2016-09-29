/*======================================================================
 
----------------------------RULE DECLARATIONS---------------------------
 
======================================================================*/

// Include library and file
#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Predicate.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the rule class
class Rule
{
    // Establish friend classes
    friend class Database;
    friend class Parser;
    friend class Graph;

    private:
        // Data Members
        string name;
        vector<Predicate> rule_head;
        vector<Predicate> rule_body;
    
    public:
        // Constructors
        Rule(){};
        Rule(string);
    
        // Member Functions
        int findIndex(string, vector<Predicate>);
        string toString();
    
        // Destructor
        virtual ~Rule();
    
};

//======================================================================