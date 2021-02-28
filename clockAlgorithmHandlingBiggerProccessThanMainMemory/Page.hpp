#ifndef _PAGE_HPP_
#define _PAGE_HPP_
/*
* Henrique Medeiros Dos Reis 
* Feb 23 2020 versrion
* page class 
*/
#include <iostream>
/*
	This class constructs a page object that will have a virtual page number, a frame that it is currently in, and the last component that tells wheater it was used soon or not.
*/
class Page
{
private: 
	//these three variables are the correspondent of the description above
	int _virtualPageNumber;
	int _pageFrameNumber;
	int _used;
public:
	//we have two constructors, this first one will set the parameter value and the the _virtual page = to that
	Page(int vPage): _virtualPageNumber(vPage), _used(0){}
	//the second one creates one that is empty
	Page() {}
	
	//this method will return a constant copy of the virtualPageNumber
	int virtualP() const;
	//this method will return a reference to the virtual pageNumber
	int& virtualP();
	
	//this method will set the page frame number to the parameter newFrame
	void frameNum(int newFrame); 
	//this method will return a reference to the virtual frameNum
	int& frameNum(); 
	
	//this method will a copy of the _used variable
	int used();
	//this method will set _used to 1
	void use();
	//this method will set _used to 0
	void unuse();
		
};
#endif




