/*======================================================================
 
----------------------------NODE DEFINITIONS----------------------------
 
======================================================================*/

// Include file
#include "Node.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the node constructor
Node::Node()
{
    post_order_number = -1;
    visited = false;
}

//======================================================================

// Define the was visited function
void Node::wasVisited()
{
    this->visited = true;
}

//======================================================================

// Define the assign post order number function
void Node::assignPostOrderNumber(int number)
{
    this->post_order_number  = number;
}

//======================================================================

// Define the insert adjacent nodes function
void Node::insertAdjacentNodes(int rule_index)
{
    dependencies.insert(rule_index);
}

//======================================================================

// Define the print adjacent nodes function
string Node::printAdjacentNodes()
{
    stringstream ss;
    
    for(auto adjacent_node : dependencies)
    {
        ss << " R" << adjacent_node;
    }
    
    return ss.str();
}

//======================================================================

// Define the get adjacent nodes function
set<int> Node::getAdjacentNodes()
{
    return this->dependencies;
}

//======================================================================

// Define the node deconstructor
Node::~Node()
{
    dependencies.clear();
}

//======================================================================