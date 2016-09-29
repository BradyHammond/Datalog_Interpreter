# Datalog Interpreter

This is the final result of BYU's CS 236 class. It includes:
* A lexical analyzer
* A parser
* A relational database
* And an interpreter
The lexical analyzer takes an input stream and converts it into tokens. The tokens are then passed to the parser to determine if the input is a valid datalog program. From there the program is broken down into relations with their own unique name, schema, and set of tuples. These relations are stored in a relational database. Finally the rules and queries from the datalog program are evaluated, and the corresponding output is given.
