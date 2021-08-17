#include "SpaceUse.hpp"
/*
	Henrique Meediros Dos Reis
	Remaining implementation of SpaceUse
	Version: mar/15/2021
*/

using namespace std;
//modifier for variable name
string&
SpaceUse::vName()
{
	return _vName;
}
//overloaded method that compares 2 SpaceUse
bool
SpaceUse::operator==(const SpaceUse &su) const
{
	return (su.vName()==_vName && su.address()==_address &&su.referenceC()==_referenceC &&su.size()==_size);
}
