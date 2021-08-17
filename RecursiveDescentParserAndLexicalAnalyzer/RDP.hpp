#ifndef _RDP_HPP_
#define _RDP_HPP_
#include <list>
#include "SpaceUse.hpp"
#include <fstream>
/*
	Henrique Medeiros Dos Reis
	Recursive Descent Parser header file.
	version: mar/15/2021
	
	this is only built of a vector that will handle the space using. And will follow the 
	rules below
*/
/*
	<prog> -> <slist>
	<slist> -> <stmt> SEMICOLON <slist> | E
	<stmt> -> FREE LPAREN VAR RPAREN | 
			  DUMP LPAREN RPAREN |
			  COMPRESS LPAREN RPAREN | 
			  VAR ASSIGN <RHS>
	<rhs> ->  ALOC LPAREN INTEGER RPAREN | 
			  VAR
*/
class RDP
{
private:
	std::list<SpaceUse> _fList;//list of SpaceUse that will represent our free list
	std::list<SpaceUse> _uList;//list of SpaceUse that will represent our used list
public:
	RDP() {}//default constructor
	
	//method that will represent our <progr> in our rule above, it needs a stream to read from, and the integer size of the list
	std::string prog(std::istream &is, int freeLSize);
	//method that will represent our <slist> in our rule above, it needs a stream to read from
	std::string slist(std::istream &is);
	//method that will represent our <stmt> in our rule above, it needs a stream to read from
	std::string stmt(std::istream &is);
	//method that will represent our <rhs> in our rule above, it needs a stream to read from, and a string with the variable
	std::string rhs(std::istream &is, std::string varName);
};
#endif 
 
