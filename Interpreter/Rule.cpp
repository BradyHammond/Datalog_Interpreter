/*======================================================================
 
----------------------------RULE DEFINITIONS----------------------------
 
======================================================================*/

// Include file
#include "Rule.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the rule constructor
Rule::Rule(string name)
{
    this->name = name;
}

//======================================================================

// Define the find index function
int Rule::findIndex(string value, vector<Predicate> names)
{
    int index = -1;
    
    for(int i = 0; i < names.size(); ++i)
    {
        if(names[i].name == value)
        {
            index = i;
        }
    }
    
    return index;
}

//======================================================================

// Define the to string function
string Rule::toString()
{
    stringstream ss;
    
    for(int i = 0; i < rule_head.size(); ++i)
    {
        ss << rule_head[i].name << "(";
        for(int j = 0; j < rule_head[i].parameter.size(); ++j)
        {
            ss << rule_head[i].parameter[j].parameter;
            
            if(j < rule_head[i].parameter.size() - 1)
            {
                ss << ",";
            }
        }
    }
    
    ss << ") :- ";
    
    for(int k = 0; k < rule_body.size(); ++k)
    {
        ss << rule_body[k].name << "(";
        for(int l = 0; l < rule_body[k].parameter.size(); ++l)
        {
            ss << rule_body[k].parameter[l].parameter;
            if(l < rule_body[k].parameter.size() - 1)
            {
                ss << ",";
            }
        }
        
        if(k < rule_body.size() - 1)
        {
            ss << "),";
        }
    }
    
    ss << ")";
    return ss.str();
}

//======================================================================

// Define the rule destructor
Rule::~Rule(){}

//======================================================================