#include <iostream>
#include "Token.hpp"
#include "RDP.hpp"
#include "SpaceUse.hpp"
#include <fstream>
/*
	Henrique Meediros Dos Reis
	simple main that will use the RDP, token and SpaceUse
	Version: mar/15/2021
*/
using namespace std;

int main(int argc, char *argv[])
{
	int freeLSize;//get the size of the free list from imput
	cout<<"Please enter the initial freelist (heap) size: ";
	cin>>freeLSize;
	string fname;//get the input file from the input
	cout<<"enter a filename: ";
	cin >>fname;
	
	ifstream ifile(fname);//open the input file
	
	RDP start;//create a RDP and start the regression by calling prog
	start.prog(ifile, freeLSize);
	
	return 0;
}


