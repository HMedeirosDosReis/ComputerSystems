#include "RDP.hpp"
#include "Token.hpp"
#include <list>
#include "SpaceUse.hpp"
using namespace std;
/*
	Henrique Meediros Dos Reis
	Implementation of RDP
	Version: mar/15/2021
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
//from the rule above, we can see that a program can only be replaced by a slist
string
RDP::prog(istream &is, int freeLSize)
{	//initialize the spaceUse that will represent the first block of a free space
	SpaceUse freeS = SpaceUse();
	freeS.address() = 0;
	freeS.size() = freeLSize;
	freeS.referenceC() = 0;
	freeS.vName() = "";
	_fList.push_back(freeS);//put it in the list
	string result = slist(is);//start the recursion going to the s list
	return result;
}
//from the rule above, we can see that a slist can be replaced by a stmt followed by a semicolon followed by a slist or nothing
string 
RDP::slist(istream &is)
{	
	string fstmt = stmt(is);//first, we solve the statment
	//next we take the next token
	Token tok;
	is>>tok;
	
	if(tok.type()==SEMICOLON)//make sure it is a semicolon
		return slist(is);//then, finally call the slist
	return "";//if we get here, then we should return "nothign"
}
// from the rule above, we can see that a statment has 4 options that need to be handled
//1 free followed by a ( followed by an integer followed by ) 
//2 dump followed by ( followed by )
//3 compress followed by ( followed by ) 
//4 var followed by = followed by rhs
string
RDP::stmt(istream &is)
{	//get the next input
	Token tok;
	is>>tok;
	if(tok.type()==FREE)//the first case happens when we have the keyword free
	{	
		is>>tok;//input the next token, which should be (
		if(tok.type()==LPAREN)//make sure it is
		{	
			is>>tok;//get the next token which should be a variable
			string varToClean = tok.value();//put the value of the token in a string variable 
			SpaceUse spaceToRemove = SpaceUse();
			for(list<SpaceUse>::iterator su = _uList.begin();su != _uList.end(); su++)//loop through the list
			{
				if(su->vName()==varToClean)//if where im now is equal to the varible i need to remove
				{	//set spaceToRemove equal to the values in this iteration
					spaceToRemove.address()=su->address();
					spaceToRemove.vName()=su->vName();
					spaceToRemove.size()=su->size();
					spaceToRemove.referenceC()=su->referenceC();
				}
			}
			_uList.remove(spaceToRemove);//remove the space to remove
			for(list<SpaceUse>::iterator su = _uList.begin();su != _uList.end(); su++)
			{	//decrement the number of references to the address we were previously
				if(su->address()==spaceToRemove.address())
					su->referenceC() = su->referenceC()-1;
			}
			spaceToRemove.vName()="";//name is no empty
			if(spaceToRemove.referenceC()<=1)//if i have no references besides the removed previouslu
			{
				spaceToRemove.referenceC()=0;//no longer have any references
				_fList.push_front(spaceToRemove);//push to the free list
				_fList.sort();//sort it 
			}
			is>>tok; //assume this will be an RPAREN
		}
	}
	else if(tok.type()==DUMP)//second case 
	{
		cout<<"Variables:"<<endl;
		for(SpaceUse su: _uList)//loop through the used list, and print it
		{
			cout<<su.vName()<<":"<<su.address()<<" ("<<su.size()<<") ["
				<<su.referenceC()<<"]"<<endl;
		}
		
		cout<<"Free List:"<<endl;
		for(SpaceUse su: _fList)//loop through the free list, and print it
		{
			cout<<su.address()<<" ("<<su.size()<<") ["
				<<su.referenceC()<<"],";
		}
		cout<<endl;
		//now, lets print the empty spaces
		
		cout<<"========================================================"<<endl;
		is>>tok;//take the LPAREN
		is>>tok;//take the RPAREN	
	}
	else if(tok.type()==COMPRESS)// 3 case
	{	
		bool canMerge=true;//i might be able to merge, so loop at least once
		while(canMerge)
		{
			canMerge=false;//dont want to keep looping if i didnt change anything before
			list<SpaceUse> newList;//initialize a list that will hold the merged values
			for(list<SpaceUse>::iterator su = _fList.begin();su != _fList.end(); su++)//loop through my free list
			{	
				list<SpaceUse>::iterator nextSU = su;//gets the next value 
				nextSU++;//gets the next value in the list
				if(su->address()+su->size() == nextSU->address())//if the sum of adress and size is my next adress
				{	//go ahead and merge
					SpaceUse merged=SpaceUse();
					merged.address()=su->address();
					merged.size()=su->size()+nextSU->size();
					merged.referenceC()=0;
					newList.push_back(merged);//since we merged, put it in the new list
					su++;//skip the next element, since we merged it
					canMerge=true;//with this new block, i might be able to merge again
				}
				else
					newList.push_back(*su);//if the sum wasnt equal, then just put it in the list
			}
			_fList=newList;//my free list is now the merged list
		}
		is>>tok;//take the LPAREN
		is>>tok;//take the RPAREN	
	}
	else if(tok.type()==VAR)// 4 case
	{
		//hande the assign, my varName is my token value
		string varName = tok.value();
		is>>tok;//get next token
		if(tok.type() == ASSIGN)
		{
			string rhside = rhs(is, varName);	//call rhs 	
		}
		
		
		
	}
	return "";
}
// from the rule above, we can see that a rhs has 2 options that need to be handled, it requires a string representing the variable on the lhs
//1 alloc followed by ( followed by an integer followed by ) 
//2 only a variable
string
RDP::rhs(istream &is, string varName)
{
	Token tok;
	is>>tok;//get the next token
	if(tok.type()==ALLOC)//if it is aloc
	{
		is>>tok;//get the next token 
		if(tok.type()==LPAREN)//make sure it is a (
		{
			//needs to find a space in the list that i can fit the required space then put it there
			is>>tok;//integer represing how much to alloc
			int valueToAlloc=atoi(tok.value().c_str());
			//loop thorugh the free list
			bool inUList = 0;
			for(list<SpaceUse>::iterator su = _uList.begin();su != _uList.end(); su++)//loop through the used list
			{
				if(su->vName()==varName)//if im refering to an existing variable, i may need to change it
				{	
					SpaceUse spaceToGiveBack=SpaceUse();//i might need to give some space back
					spaceToGiveBack.size() = su->size()-valueToAlloc;
					spaceToGiveBack.address() = su->address() +valueToAlloc;
					spaceToGiveBack.referenceC()=0;
					_fList.push_front(spaceToGiveBack);//give it to the free list
					_fList.sort();//sort it
					
					su->size() = valueToAlloc;
					inUList=1;//im in used list now
				}
			}
			if(!inUList)//if i wasnt added previously 
			{
				for(list<SpaceUse>::iterator su = _fList.begin();su != _fList.end(); su++)//loop trough the list
				{
					if(su->size()>valueToAlloc)//the current block has enough space?
					{	//if so, create the space
						SpaceUse spaceToAlloc=SpaceUse();
						spaceToAlloc.size()=valueToAlloc;
						spaceToAlloc.address()=su->address();
						spaceToAlloc.referenceC()=1;
						spaceToAlloc.vName() = varName;
						_uList.push_front(spaceToAlloc);//put it in the used list
						
						su->size()=su->size()-valueToAlloc;
						su->address()=su->address()+valueToAlloc;
						break;
					}
				}
			}
			
			is>>tok; //assume this will be an RPAREN
		}
	}
	else if(tok.type()==VAR)//in case we are a var
	{	
		for(list<SpaceUse>::iterator su = _uList.begin();su != _uList.end(); su++)//loop through the used list
		{
			if(tok.value()==varName)//if im refering to myself, do nothing
				break;
			if( su->vName()==tok.value())//if im refering to this iteration
			{	//create the space
				SpaceUse newSpace;
				newSpace.vName()=varName;
				newSpace.address()=su->address();
				newSpace.referenceC()=su->referenceC()+1;
				newSpace.size()=su->size();
				_uList.push_front(newSpace);//put it in the used list
				su->referenceC() = newSpace.referenceC();
				break;
			}
			
		}
	}
	return "";
}



