#ifndef _SPACE_USE_HPP_
#define _SPACE_USE_HPP_
/*
	Henrique Medeiros Dos Reis
	SpaceUse header file.
	version: mar/15/2021
	
	A SpaceUse is the representation of a variable in this program, its goal is to keep acount of a variable name, the number of references that this variable currently has, the size of the allocation that this variable requires, the address which this variable is currently stored on, and weather I am using this variable or not.
*/
#include <string>

class SpaceUse
{
private:
	int _address;//location of this variable
	int _referenceC;//number of references to this variable location
	int _size;//the size that this variable requires
	std::string _vName;//variable's name
	bool _used;//am i being used?
public:
	SpaceUse(): _used(false) {}//constuctor for a SpaceUse
	
	//accessor and modifiers for address
	int address() const {return _address;}
	int& address() {return _address;}
	//accessor and modifiers for reference count
	int referenceC() const {return _referenceC;}
	int& referenceC() {return _referenceC;}
	//accessor and modifiers for size
	int size() const {return _size;}
	int& size() {return _size;}
	//accessor and modifiers for used
	bool used() const {return _used;}
	bool& used() {return _used;}
	//accessor and modifiers for vName
	std::string vName() const{return _vName;}
	std::string& vName();
	
	//overloaded operador, may be used if sorting is needed
	bool operator<(const SpaceUse &su) const {return _address<su.address();}
	//overloaded operator to compare 2 SpaceUse
	bool operator==(const SpaceUse &su) const;
	
};
#endif 
