#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>
#include <string>
/*
	Henrique Medeiros Dos Reis
	Token header file
	version: mar/15/2021
*/

//the following constants will represent the token types
#define ERROR -1
#define NONE 0
#define INTEGER 1
#define VAR 2
#define FREE 3
#define DUMP 4
#define COMPRESS 5
#define ALLOC 6
#define SEMICOLON 7
#define LPAREN 8
#define RPAREN 9
#define ASSIGN 10

class Token
{
private://a token is composed of a type and a value
	int _type;
	std::string _value;
public:
	Token(): _type(NONE), _value(""){}// constructor for a token, sets type to 0 and value to the empty string
	
	//accessor and modifiers for token type
	int type() const {return _type;} 
	int& type() {return _type;}
	//accessor and modifiers for token value
	std::string value()const {return _value;}
	std::string& value() {return _value;}
	
	//print the token to the given stream
	std::ostream& print(std::ostream &os) const {os<< _value;return os;}
	//reads the token from the given stream
	std::istream& read(std::istream &is);
	
	//overloaded operators 
	friend std::ostream& operator<<(std::ostream &os, const Token &t);
	friend std::istream& operator>>(std::istream &is, Token &t);
};

#endif
