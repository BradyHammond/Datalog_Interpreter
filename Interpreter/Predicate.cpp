/*======================================================================
 
-------------------------PREDICATE DEFINITIONS--------------------------
 
======================================================================*/

// Include file
#include "Predicate.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the predicate constructor
Predicate::Predicate (string name)
{
    this->name = name;
}

//======================================================================

// Define the to string function
string Predicate::toString()
{
    stringstream ss;
    
    ss << name << "(";
    for(int i = 0; i < parameter.size(); ++i)
    {
        ss << parameter[i].parameter;
        if(i != parameter.size() - 1)
        {
            ss << ",";
        }
    }
    ss << ")";
    
    return ss.str();
}

//======================================================================

// Define the predicate destructor
Predicate::~Predicate(){}

//======================================================================