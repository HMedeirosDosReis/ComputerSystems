/*
* Henrique Medeiros Dos Reis 
* Feb 23 2020 versrion
* page class implementation
*/
#include "Page.hpp"
//this method will return a constant copy of the virtualPageNumber
int
Page::virtualP() const
{
	return _virtualPageNumber;
}

//this method will return a reference to the virtual pageNumber
int&
Page::virtualP() 
{
	return _virtualPageNumber;
}

//this method will set the page frame number to the parameter newFrame
void
Page::frameNum(int newFrame)
{
	_pageFrameNumber = newFrame;
}

//this method will return a reference to the virtual frameNum
int&
Page::frameNum()
{
	return _pageFrameNumber;
}

//this method will a copy of the _used variable
void
Page::use()
{
	_used=1;
}

//this method will set _used to 1
void
Page::unuse()
{
	_used=0;
}

//this method will set _used to 0
int
Page::used()
{
	return _used;
}
	
