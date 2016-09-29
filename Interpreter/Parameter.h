/*======================================================================
 
-------------------------PARAMETER DECLARATIONS-------------------------
 
======================================================================*/

// Include libraries and file
#pragma once
#include <stdio.h>
#include <string>

// Setup namespace
using namespace std;

//======================================================================

class Parameter
{
    // Establish friend classes
    friend class Predicate;
    friend class Rule;
    friend class Database;

    private:
        // Data Member
        string parameter;
    
    public:
        // Constructor
        Parameter(string);

        // Member Functions
        string toString();
    
        // Destructor
        virtual ~Parameter();
};

//======================================================================