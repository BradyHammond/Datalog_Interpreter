/*======================================================================
 
----------------------------NODE DECLARATIONS---------------------------
 
======================================================================*/

// Include libraries
#pragma once
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <set>

// Setup namespace
using namespace std;

//======================================================================

// Create the node class
class Node : public vector<string>
{
    // Establish friend classes
    friend class Graph;

    private:
        // Data Members
        int post_order_number;
        bool visited;
        set<int> dependencies;
    
    public:
        // Constructor
        Node();
    
        // Member functions
        void wasVisited();
        void assignPostOrderNumber(int);
        void insertAdjacentNodes(int);
        string printAdjacentNodes();
        set<int> getAdjacentNodes();
    
        // Destructor
        ~Node();
};

//======================================================================