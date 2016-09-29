/*======================================================================
 
--------------------------SCANNER DEFINITIONS---------------------------
 
======================================================================*/

// Include libraries and file
#include "Scanner.h"

// Setup namespace
using namespace std;

//======================================================================

// Define variables
bool Scanner::error_flag = false;

//======================================================================

// Define the scanner constructor
Scanner::Scanner()
{
    line_number = 1;
    scanner_string = "";
    string_identifier = "";
    comment = "";
    current_token = 0;
}

//======================================================================

// Define the next token function
void Scanner::nextToken()
{
    current_token++;
}

//======================================================================

// Define the get type function
TokenType Scanner::getType()
{
    return token_list[current_token].getTokenType();
}

//======================================================================

// Define the get token function
string Scanner::getToken()
{
    return token_list[current_token].toString();
}

//======================================================================

// Define the is end function
bool Scanner::isEnd(ifstream &file)
{
    if (file.eof() || file.peek() == EOF)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

//======================================================================

// Define the is file empty function
bool Scanner::isFileEmpty(string filename)
{
    ifstream file;
    file.open(filename);
    char current_character = ' ';
    vector<char> empty;
    
    while(!file.eof())
    {
        file.get(current_character);
        empty.push_back(current_character);
    }
    
    if(empty.size() <= 1 && line_number == 1)
    {
        empty.clear();
        return true;
    }
    
    else
    {
        return false;
    }
    
    return true;
}

//======================================================================

// Define the sub scan function
bool Scanner::subScan(ifstream &file, char current_character)
{
    if(current_character == '\n')
    {
        return true;
    }
    
    else if(file.eof())
    {
        return true;
    }
    
    else
    {
        return false;
    }
    
    return false;
}

//======================================================================

// Define the get file function
void Scanner::getFile(string filename, string output_file, char current_character)
{
	ifstream file;    
    
    file.open(filename.c_str());
	if(file.fail())
	{
		cout << "The file name \"" << filename << "\" couldn't be open.\n";
		return;
	}
    
    if(isFileEmpty(filename) == true)
    {
        token_list.push_back(Token(ENDOF, "", line_number));
        return;
    }
    
	else
	{
        scan(file, output_file);

        if(Scanner::error_flag == true)
        {
            return;
        }
        
        else
        {
            token_list.push_back(Token(ENDOF, "", line_number));
            return;
        }
	}
}

//======================================================================

// Define the is keyword function
bool Scanner::isKeyword(ifstream &file, char current_character, vector<Token> &token_list)
{
    if(string_identifier == "Queries")
    {
        token_list.push_back(Token(QUERIES, "Queries", line_number));
        return true;
    }
    
    else if(string_identifier == "Facts")
    {
        token_list.push_back(Token(FACTS, "Facts", line_number));
        return true;
    }
    
    else if(string_identifier == "Rules")
    {
        token_list.push_back(Token(RULES, "Rules", line_number));
        return true;
    }
    
    else if(string_identifier == "Schemes")
    {
        token_list.push_back(Token(SCHEMES, "Schemes", line_number));
        return true;
    }
   
    return false;
}

//======================================================================

// Define the scan identifier function
void Scanner::scanIdentifier(ifstream &file, char current_character, vector<Token> &token_list, string output_file)
{
	if(isalpha(current_character))
    {
        string_identifier = "";
        string_identifier += current_character;
        
        while(isalnum(current_character) && isalnum(file.peek()))
        {
            file.get(current_character);
            string_identifier += current_character;
        }
        
        if(isKeyword(file, current_character, token_list) == false)
        {
            token_list.push_back(Token(ID, string_identifier, line_number));
            return;
        }
    }
    
    else
    {
        Scanner::error_flag = true;
    }
}

//======================================================================

// Define the scan string function
void Scanner::scanString(ifstream &file, char current_character, vector<Token> &token_list, string output_file)
{
    bool error = false;
    scanner_string = "";
    scanner_string = current_character;
    
	while(file.peek() != '\'')
    {
        if(file.eof())
        {
            error = true;
            break;
        }
        
        else if(file.peek() == '\n')
        {
            error = true;
            break;
        }
        
        else
        {
            file.get(current_character);
            scanner_string += current_character;
        }
    }
    
    if(error == true)
    {
        error_flag = true; 
    }
    
    else
    {
        file.get(current_character);
        scanner_string += current_character;
        token_list.push_back(Token(STRING,scanner_string,line_number));
    }
}

//======================================================================

// Define the swap function
void Scanner::swap(ifstream &file, char current_character, vector<Token> &token_string, string output_file)
{  
    if(error_flag != true)
    {
        switch (current_character)
        {
            case ',':
                token_list.push_back(Token(COMMA, ",", line_number));
                break;
                
            case '.':
                token_list.push_back(Token(PERIOD, ".", line_number));
                break;
                
            case '?':
                token_list.push_back(Token(Q_MARK, "?", line_number));
                break;
                
            case ':':
                if (file.peek() == '-')
                {
                    token_list.push_back(Token(COLON_DASH, ":-", line_number));
                    file.get(current_character);
                    break;
                }
                
                else
                {
                    token_list.push_back(Token(COLON, ":", line_number));
                    break;
                }
                
            case '(':
                token_list.push_back(Token(LEFT_PAREN, "(", line_number));
                break;
                
            case ')':
                token_list.push_back(Token(RIGHT_PAREN, ")", line_number));
                break;
                
            case '+':
                token_list.push_back(Token(ADD, "+", line_number));
                break;
                
            case '*':
                token_list.push_back(Token(MULTIPLY, "*", line_number));
                break;
                
            case '#':
                file.ignore(1000, '\n');
                line_number++;
                break;
                
            case '\'':
                scanString(file, current_character, token_list, output_file);
                break;
                
            default:
                scanIdentifier(file, current_character, token_list, output_file);
                break;
        }
    }
}

//======================================================================

// Define the scan function
void Scanner::scan(ifstream &file, string output_file)
{
    char current_character = '0';
    
    while(!file.eof() || error_flag != true)
    {
        file.get(current_character);
        
        if(subScan(file, current_character) == true)
        {
            line_number++;
        }
        
        else if(!isspace(current_character) && current_character != '\n')
        {
            swap(file, current_character, token_list, output_file);

            if(error_flag == true)
            {
                break;
            }
        }
        
        if(isEnd(file) == true)
        {
            break;
        }
    }
}

//======================================================================

// Define the print function
void Scanner::print(string output_file)
{
    string output;
    ofstream fout(output_file);
    
    string vector_size;
    
    stringstream ss;
    ss << token_list.size();
    ss.str();
    ss >> vector_size;
    
    for(int i = 0; i < token_list.size(); ++i)
    {
        output += token_list[i].toString() + "\n";
    }
    
    if(Scanner::error_flag == true)
    {
        string actual_line_number;
        stringstream number;
        number << line_number;
        number.str();
        number >> actual_line_number;
        
        output += "Input Error on line " +  actual_line_number;
        fout << output;
        
    }
    else if(token_list.size() > 0 && Scanner::error_flag == false)
    {
        output += "Total Tokens = " + vector_size;
        fout << output;
    }
    
    token_list.clear();
    fout.close();
}

//======================================================================

// Define the scanner destructor
Scanner::~Scanner(){}

//======================================================================