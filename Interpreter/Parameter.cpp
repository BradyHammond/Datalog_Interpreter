/*======================================================================
 
-------------------------PARAMETER DEFINITIONS--------------------------
 
======================================================================*/

// Include libraries and file
#include "Parameter.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the parameter constructor
Parameter::Parameter(string parameter)
{
    this->parameter = parameter;
}

//======================================================================

// Define the to string function
string Parameter::toString()
{
    return parameter;
}

//======================================================================

// Define the parameter destructor
Parameter::~Parameter(){}

//======================================================================