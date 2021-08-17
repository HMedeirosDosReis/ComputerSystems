/*
	Henrique Meediros Dos Reis
	Implementation of Token
	Version: mar/15/2021
*/

#include "Token.hpp"

using namespace std;

//table that wull represent the DFA
static int **DFA=nullptr;

std::istream&
Token::read(std::istream &is)
{
	if(DFA==nullptr)	//if diagram table is not built yet
	{
		DFA=new int*[ASSIGN+1];//initialize the table to the size of the last possible operation +1
		for(int currState=0; currState<=ASSIGN;currState++)
		{	//in the beggining, all transitions are errors
			DFA[currState] = new int[256];
			for(int ch=0; ch<256; ch++)
				DFA[currState][ch] = ERROR;
		}
		
		//state 0 we can have any number or letter
		for(char ch='0'; ch<'9'; ch++)
			DFA[0][(int) ch] = INTEGER;
		for(char ch='A'; ch<'Z'; ch++)
			DFA[0][(int) ch] = VAR;
		for(char ch='a'; ch<'z'; ch++)
			DFA[0][(int) ch] = VAR;
		//or we can have speacial casses
		DFA[0][';'] = SEMICOLON;
		DFA[0]['('] = LPAREN;
		DFA[0][')'] = RPAREN;
		DFA[0]['='] = ASSIGN;
		
		//state 1 and beyond
		//after state 1, we can either have variable names, or integers 
		for(int currState=1; currState<=ASSIGN;currState++)
		{	
			for(char ch='0'; ch<'9'; ch++)
				DFA[currState][(int) ch] = INTEGER;
			for(char ch='A'; ch<'Z'; ch++)
				DFA[currState][(int) ch] = VAR;
			for(char ch='a'; ch<'z'; ch++)
				DFA[currState][(int) ch] = VAR;
		}
	}
	
	//set the default
	_value = "";
	_type = ERROR;
	
	int curr=0;
	int prev=ERROR;
	
	//pick the first character  skipping whitespace
	char ch;
	is>>ch;
	if(!is)
		return is;	
	is.putback(ch);
	
	//loop until we are in an ERROR position
	while(curr!=ERROR)
	{
		ch = is.get();//pick the next charater
		prev = curr;//previous value is curr
		curr=DFA[curr][(int) ch];//update curr to the value in the table
		//in case I have a case that I should quit the loop, do so
		if(prev==ASSIGN || prev==LPAREN || prev==LPAREN || prev==SEMICOLON)
			break;
		if(curr!=ERROR)//if not, keep adding these values to the _value
			_value+=ch;
		
	}
	if(is)//the last character is not a part of the previrous token, put it back
		is.putback(ch);
	//handle my special keywords
	if(_value=="free")
		_type=FREE;
	else if(_value=="dump")
		_type=DUMP;
	else if(_value=="compress")
		_type=COMPRESS;
	else if(_value=="alloc")
		_type=ALLOC;
	else//in case im not a keyword, my type is the type before the error
		_type=prev;
	
	return is;
}
//overloaded method to print the token
std::ostream& operator<<(std::ostream &os, const Token &t)
{
	return t.print(os);
}
//overloaded method to read the token
std::istream& operator>>(std::istream &is, Token &t)
{
	return t.read(is);
}
