/*======================================================================
 
---------------------------TOKEN DEFINITIONS----------------------------
 
======================================================================*/

// Include file
#include "Token.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the token constructor
Token::Token(TokenType type, string id, int line_number)
{
    this->type = type;
    this->id = id;
    this->line_number = line_number;
}

//======================================================================

// Define the get token type function
TokenType Token::getTokenType()
{
    return type;
}

//======================================================================

// Define the get ID function
string Token::getID()
{
    return id;
}

//======================================================================

// Define the get line number function
int Token::getLineNumber()
{
    return line_number;
}

//======================================================================

// Define the to string function
string Token::toString()
{
    string output;
    string actual_line_number;

    stringstream ss;
    ss << getLineNumber();
    ss.str();
    ss >> actual_line_number;

    output = "(" + token_map[getTokenType()] + ",\"" + getID() + "\"," + actual_line_number + ")";

    return output;
}

//======================================================================

// Define the token destructor
Token::~Token(){}

//======================================================================

