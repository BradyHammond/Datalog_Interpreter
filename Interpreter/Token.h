/*======================================================================
 
---------------------------TOKEN DECLARATIONS---------------------------
 
======================================================================*/

// Include libraries
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <sstream>

// Setup namespace
using namespace std;

//======================================================================

// Define token type options
enum TokenType
{
    COMMA,
    PERIOD,
    Q_MARK,
    COLON,
    COLON_DASH,
    LEFT_PAREN,
    RIGHT_PAREN,
    ADD,
    MULTIPLY,
    FACTS,
    QUERIES,
    RULES,
    ID,
    STRING,
    WHITESPACE,
    UNDEFINED,
    ENDOF,
    SCHEMES
};

//======================================================================

// Create the token class
class Token
{
    private:
        // Data Members
        string id;
        TokenType type;
        int line_number;
        map<TokenType, string> token_map =
        {
            { COMMA, "COMMA" },
            { PERIOD, "PERIOD" },
            { Q_MARK, "Q_MARK" },
            { COLON, "COLON" },
            { COLON_DASH, "COLON_DASH" },
            { LEFT_PAREN, "LEFT_PAREN" },
            { RIGHT_PAREN, "RIGHT_PAREN" },
            { ADD, "ADD" },
            { MULTIPLY, "MULTIPLY" },
            { FACTS, "FACTS" },
            { QUERIES, "QUERIES" },
            { RULES, "RULES" },
            { ID, "ID" },
            { STRING, "STRING" },
            { WHITESPACE, "WHITESPACE" },
            { ENDOF, "EOF" },
            { SCHEMES, "SCHEMES" }
        };

    public:
        // Constructor
        Token(){};
    
        // Member Functions
        Token(TokenType, string, int);
        virtual TokenType getTokenType();
        virtual string getID();
        virtual int getLineNumber();
        virtual string toString();
    
        // Destructor
        virtual ~Token();
};

//======================================================================