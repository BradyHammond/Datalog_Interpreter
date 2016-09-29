/*======================================================================
 
---------------------------GRAPH DECLARATIONS---------------------------
 
======================================================================*/

// Include libraries and files
#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include "Node.h"
#include "Rule.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the graph class
class Graph
{
    // Establish friend classes
    friend class Database;

    private:
        // Data Members
        int postorder;
        vector<Rule> rules;
        map<int, Node> graph;
        map<int, Node> reverse_graph;
        map<int, set<int>> scc;
    
    public:
        // Constructors
        Graph(){};
        Graph(vector<Rule>&);
    
        // Member Functions
        void addDependencies(int);
        void makeGraphs();
        void dfs(int);
        void dfsForest();
        vector<int> getHighestToLowestPON();
        void sccInDfs(int, set<int>&);
        void findScc();
        string printGraph();
        string printReverseGraph();
        string printScc();
    
        // Destructor
        ~Graph();
};

//======================================================================
