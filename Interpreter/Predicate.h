/*======================================================================
 
-------------------------PREDICATE DECLARATIONS-------------------------
 
======================================================================*/

// Include libraries and file
#pragma once
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the predicate class
class Predicate
{
    // Establish friend classes
    friend class Database;
    friend class Rules;
    friend class Graph;

    public:
        // Data Members
        string name;
        vector<Parameter> parameter;
    
    public:
        // Constructors
        Predicate(){};
        Predicate(string);
    
        // Member Function
        string toString();
    
        // Destructor
        virtual ~Predicate();
};

//======================================================================