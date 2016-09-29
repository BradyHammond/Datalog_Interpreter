/*======================================================================
 
--------------------------SCANNER DECLARATIONS--------------------------
 
======================================================================*/

// Include libraries and file
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cctype>
#include "Token.h"

// Setup namespace
using namespace std;

//======================================================================

// Create the scanner class
class Scanner : public Token
{
    // Establish friend class
    friend class Parser;

    private:
        // Data Members
        int line_number;
        string scanner_string, string_identifier, comment;
        vector<Token> token_list;
        int current_token;

    public:
        // Constructor
        Scanner();
	
        // Data Member
        static bool error_flag;
    
        // Member Functions
        virtual void nextToken();
        virtual TokenType getType();
        virtual string getToken();
        virtual bool isEnd(ifstream &);
        virtual bool isFileEmpty(string);
        virtual bool subScan(ifstream &, char);
        virtual void getFile(string, string, char);
        virtual bool isKeyword(ifstream &, char, vector<Token> &);
        virtual void scanIdentifier(ifstream &, char, vector<Token> &, string);
        virtual void scanString(ifstream &, char, vector<Token> &, string);
        virtual void swap(ifstream &, char, vector<Token> &, string);
        virtual void scan(ifstream &, string);
        virtual void print(string);
    
        // Destructor
    	virtual ~Scanner();
};

//======================================================================