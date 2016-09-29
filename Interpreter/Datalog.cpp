/*======================================================================
 
---------------------------DATALOG DEFINITIONS--------------------------
 
======================================================================*/

// Include library and file
#include <algorithm>
#include "Datalog.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the datalog constructor
Datalog::Datalog(){}

//======================================================================

// Define the domain search function
bool Datalog::domainSearch(string value)
{
    for(int i = 0; i < myDomain.size(); ++i)
    {
        if(myDomain[i] == value)
        {
            return true;
        }
    }
    
    return false;
}

//======================================================================

// Define the add schemes function
void Datalog::addSchemes(Predicate predicate)
{
    mySchemes.push_back(predicate);
}

//======================================================================

// Define the add facts function
void Datalog::addFacts(Predicate predicate)
{
    myFacts.push_back(predicate);
}

//======================================================================

// Define the add rules function
void Datalog::addRules(Rule predicate)
{
    myRules.push_back(predicate);
}

//======================================================================

// Define the add queries function
void Datalog::addQueries(Predicate predicate)
{
    myQueries.push_back(predicate);
}

//======================================================================

// Define the add domain function
void Datalog::addDomain(string value)
{
    if(domainSearch(value) == false)
    {
        myDomain.push_back(value);
    }
    
    return;
}

//======================================================================

// Define the to string function
string Datalog::toString()
{
    stringstream ss;
    
    ss << "Schemes(" << mySchemes.size() << "):\n";
    for(int i = 0; i < mySchemes.size(); ++i)
    {
        ss << "  " << mySchemes[i].toString() << endl;
    }
    
    ss << "Facts(" << myFacts.size() << "):\n";
    for(int i = 0; i < myFacts.size(); ++i)
    {
        ss << "  " << myFacts[i].toString() << endl;
    }
    
    ss << "Rules(" << myRules.size() << "):\n";
    for(int i = 0; i< myRules.size(); ++i)
    {
        ss << "  " << myRules[i].toString() << endl;
    }
    
    ss << "Queries(" << myQueries.size() << "):\n";
    for(int i = 0; i < myQueries.size(); ++i)
    {
        ss << "  " << myQueries[i].toString() << endl;
    }
    
    sort(myDomain.begin(),myDomain.end());
    if(myDomain.size() == 0)
    {
        ss << "Domain(" << myDomain.size() << "):";
    }
    
    else
    {
        ss << "Domain(" << myDomain.size() << "):\n";
        for(int i = 0; i < myDomain.size(); ++i)
        {
            if(i != myDomain.size() - 1)
            {
                ss << "  " << myDomain[i] << "\n";
            }
            
            else
            {
                ss << "  " << myDomain[i];
            }
            
        }
    }
    
    return ss.str();
}

//======================================================================

// Define the clear function
void Datalog::clear()
{
    mySchemes.clear();
    myFacts.clear();
    myRules.clear();
    myQueries.clear();
    myDomain.clear();
}

//======================================================================

// Define the string value function
void Datalog::stringValue(vector<Predicate> predicate, vector<string> &string_value)
{
    for(int i = 0; i < predicate.size(); ++i)
    {
        string_value.push_back(predicate[i].name);
    }
}

//======================================================================

// Define the datalog destructor
Datalog::~Datalog(){}

//======================================================================
