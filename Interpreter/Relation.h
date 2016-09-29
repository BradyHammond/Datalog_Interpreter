/*======================================================================
 
--------------------------RELATION DECLARATIONS-------------------------
 
======================================================================*/

// Include libraries and files
#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include "Tuple.h"
#include "Scheme.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the relation class
class Relation
{
    // Establish friend classes
    friend class Database;

    private:
        // Data Members
        string name;
        Scheme schemes_list;
        set<Tuple> tuples;

    public:
        // Constructor
        Relation(string name);
    
        // Member Functions
        Relation select(int, string);
        Relation selectCompare(int, int);
        Relation project(vector<int>);
        Relation rename(vector<string>);
        vector<pair<int, int>> sameAttributes(Relation);
        bool canJoin(Tuple, Tuple, vector<pair<int, int>>);
        string makeUnion(Relation);
        Relation join(Relation);
        Scheme joinScheme(Relation);
        Tuple joinTuples(Tuple, Tuple, vector<pair<int, int>>);
        Tuple makeProduct(Tuple, Tuple);
        string toString();
    
        // Destructor
        virtual ~Relation();
};

//======================================================================