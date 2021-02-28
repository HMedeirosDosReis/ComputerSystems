/*
* Henrique Medeiros Dos Reis 
* Feb 23 2020 versrion
* project 1 CSC45500
*/
#include "Page.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{	
	//initialize variables that will hold the block, the last element that i looked at, the number of page faults,
	// the number of addresses looked
	int blockSize;
	int lastIn;
	int pageFaults=0;
	int looked=0;
	//get the block size from the input
	cout<<"Enter block size (in bytes): ";
	cin>>blockSize;
	//get the memory size from the input
	int memorySize;
	cout<<"Enter memory size (in bytes, must be a multiple of block size): ";
	cin>>memorySize;
	//in case the the memory size is not a multiple of the block size, keep asking the user to enter a new number
	while(memorySize%blockSize != 0)
	{
		cout<<"The memory size needs to be a multiple of the block size! Enter it again: ";
		cin>>memorySize;
	}
	//get the proccess size from the input 
	int processSize;
	cout<<"Enter process size (in bytes): ";
	cin>>processSize;
	//the number of blocks is equal to the memorySize divided by the blockSize
	int numberOfBlocks = memorySize/blockSize;
	//the variable of mySize will represent the size of my pageTable, which should be the proccess size divided by the block size 
	int mySize = processSize / blockSize;
	int usedBlocks =0;
	//creates a vector for the page table
	std::vector<Page> pageTable;
	//creater a vector that will represent what is in memory at this moment
	std::vector<Page> inMemory;
	//initialize the whole pageTable, this table simply has the page numbers in order 
	for(int i=0; i<=mySize; i++)
	{
		pageTable.push_back(Page(i));
	}
	
	while(1)
	{	
		bool onClock=0;//this will hold weather i needed the clock algorithm or not
		bool pageF=true;//to begin with, ill always have a page fault
		//get the virtual address from input
		int virtualAddress;
		cout<<"Enter a virtual address for the process: ";
		cin>>virtualAddress;
		//if my virtual address is bigger than 0, then i need to find the physical address
		if(virtualAddress >= 0)
		{
			int physicAddress=0;//start the physical adrress to 0
			int pageN = virtualAddress/blockSize;//the page I am is the virtual address/block size
			int offSet = virtualAddress%blockSize;//my offset is the remainder from 
			int pageFrame;
			std::vector<Page>::iterator it;
			int isInMem=0;
			// check if im in the first table already or not before doing this, if im not in the memory already
			for(it=inMemory.begin(); it!=inMemory.end();it++)
			{	int i=0;
				if(pageN==it->virtualP())
				{	//in case the page number that im looking for is equal to the virtual page , set the page frame
					inMemory[i].use();
					pageF=0;//this is not a page fault anymore
					isInMem=1;//tell we are in the memory
					pageFrame = it->frameNum();
				}
				else // if it is not, then set the item _used to 0
					inMemory[i].unuse();
				i++;
			}
			if(isInMem==0)//if im not in memory already, then do this
			{
				for(it=pageTable.begin(); it!=pageTable.end(); it++)
				{	
					//loop thorugh the whole page table
					int i=0;
					
					if(pageN==it->virtualP())
					{	//in case the page number that im looking for is equal to the virtual page
						if(usedBlocks < numberOfBlocks)//if the number of used blocks is smaller than what i can have in total
						{	//create a page and put it in the memory, it is page fault
							it->frameNum() = usedBlocks;
							Page thisPage = Page(pageN);
							thisPage.frameNum(usedBlocks);
							thisPage.use();
							inMemory.push_back(thisPage);
							usedBlocks++;
							pageF=1;
						}
						
						else //if i get here, i need the clock algorithm to figure out who we should kick out
						{	
							int notAdded=1;//i havent put in the memory yet
							while(notAdded)
							{
								if(lastIn ==usedBlocks-1)// if I was in the last position, go to the top
								{
									std::vector<Page>::iterator it2;
									for(it2=inMemory.begin(); it2!=inMemory.end();it2++)
									{	//loop through the memory
										int i2=0;
										if(inMemory[i].used() == 1)//if im marked as used, mark as unused
											inMemory[i].unuse();
										else if(inMemory[i].used()==0)//if im not marked used
										{	//go ahead and put it in the memory 
											inMemory[i].virtualP() = pageN;
											inMemory[i].use();
											pageFrame = it->frameNum();
											notAdded=0;//i have been added
										}
										i2++;
									}
								}
								else 
								{	
									//then i, not in the last place, just move foward starting from where i was, since i was not the last element
									for(int i=lastIn+1; i<=usedBlocks; i++)
									{
										if(inMemory[i].used() ==1)//if im marked as used, mark as unused
											inMemory[i].unuse();
										else if(inMemory[i].used()==0)//if im not marked used
										{	//go ahead and put it in the memory
											inMemory[i].virtualP() = pageN;
											inMemory[i].use();
											pageFrame = inMemory[i].frameNum();
											notAdded=0;//i have been added
											onClock=1;//and i used the clock
										}
									}
								}
							}
						}
						if(!onClock)
						{
							pageFrame = it->frameNum();	
							i++;
						}
					}
				}	
			}
			physicAddress =(pageFrame * blockSize)+offSet;//the physical address is equal to (pageFrame * blockSize)+offSet
			lastIn = pageFrame;//the last one position i was in the the page frame
			cout<<physicAddress;
			looked++;//increase the number of address i looked up
			if(pageF)
			{
				cout<<" *";
				pageFaults++;//increase the number of page faults
			}
			cout<<endl;
		}
		else// if im here, then the input was negative, then go ahead and print the results
		{
			cout<<"There were "<<pageFaults<<" page faults"<<endl;
			double rate =double(pageFaults)/looked;
			cout<<"Giving a page fault rate of "<<rate <<endl;
			return 0;
		}
	}
	return 0;
}
