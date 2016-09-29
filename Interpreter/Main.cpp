/*======================================================================
 
----------------------------------MAIN----------------------------------
 
======================================================================*/

// Include libraries and files
#include <iostream>
#include <string>
#include "Database.h"
#include "Parser.h"

// Setup namespace
using namespace std;

//======================================================================

// Define the main function
int main(int argc, const char * argv[]) {

    Database database;
    Parser parser;
    
    char current_character = ' ';
    string input_file = argv[1];
    string output_file = argv[2];
    
    parser.checkFile(input_file, output_file, current_character);
    parser.parseDatalogProgram();
    parser.print(output_file);
    
    database.loadDatalog(parser.getDatalog());
    database.print(output_file);
    
    return 0;
}

//======================================================================