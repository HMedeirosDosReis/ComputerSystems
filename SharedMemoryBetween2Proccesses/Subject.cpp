/*
Henrique Medeiros Dos Reis
Oct 31 2020 version
project 2 CSC35500 
*/
#include <cstdlib>
#include <iostream>
#include <sys/shm.h>
#include <sys/sem.h>
using namespace std;

int main(int argc, char *argv[])
{	
	int semKey = 7342;//define an integer that will hold the semaphore key
	int sem_id=semget(semKey, 1, IPC_CREAT|IPC_EXCL|0600);//try to open the semaphore
	if(sem_id<=0)//if it fails, open the existing one
		sem_id=semget(semKey, 1, 0);
	/*this code is probably very ineficient, since I have a bunch of separeted variables.
	 but for now it is the only way that i could think of, and worked. And I cannot use loops
	 because my variable names are different*/
	 //initialize an integer for every shared memory that I will game, this will hold the id of the memory
	int shm_id0, shm_id1, shm_id2, shm_id3, shm_id4, shm_id5, shm_id6,shm_id7,shm_id8, shm_id9;
	//initialize a variable and define the value to be the key for the shared memory
	int shmKey0, shmKey1, shmKey2, shmKey3, shmKey4, shmKey5, shmKey6, shmKey7, shmKey8, shmKey9;
	shmKey0=4200; shmKey1=4201;shmKey2=4202;shmKey3=4203;shmKey4=4204;
	shmKey5=4205;shmKey6=4206;shmKey7=4207;shmKey8=4208;shmKey9=4209;
	//try to open the shared memories
	shm_id0 = shmget(shmKey0, 1024,0);
	shm_id1 = shmget(shmKey1, 1024,0);
	shm_id2 = shmget(shmKey2, 1024,0);
	shm_id3 = shmget(shmKey3, 1024,0);
	shm_id4 = shmget(shmKey4, 1024,0);
	shm_id5 = shmget(shmKey5, 1024,0);
	shm_id6 = shmget(shmKey6, 1024,0);
	shm_id7 = shmget(shmKey7, 1024,0);
	shm_id8 = shmget(shmKey8, 1024,0);
	shm_id9 = shmget(shmKey9, 1024,0);
	//in case any of those fail
	if(shm_id0<=0)//dont have the shared memory
		shm_id0 = shmget(shmKey0, 1024, IPC_CREAT|IPC_EXCL|0666);//create one then 
	if(shm_id1<=0)
		shm_id1 = shmget(shmKey1, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id2<=0)
		shm_id2 = shmget(shmKey2, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id3<=0)
		shm_id3 = shmget(shmKey3, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id4<=0)
		shm_id4 = shmget(shmKey4, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id5<=0)
		shm_id5 = shmget(shmKey5, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id6<=0)
		shm_id6 = shmget(shmKey6, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id7<=0)
		shm_id7 = shmget(shmKey7, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id8<=0)
		shm_id8 = shmget(shmKey8, 1024, IPC_CREAT|IPC_EXCL|0666);
	if(shm_id9<=0)
		shm_id9 = shmget(shmKey9, 1024, IPC_CREAT|IPC_EXCL|0666);
	
	while(1)
	{	
		struct sembuf semCommand[1];//create a semaphore buffer
		//tell the semaphore to wait until I have something in the gift table
  		semCommand[0].sem_num=0;
  		semCommand[0].sem_op=-1;
  		semCommand[0].sem_flg=0;
  		int semResult = semop(sem_id, semCommand, 1);
		if (semResult==-1)
		{
			cerr << "Unable to wait on samaphore"  << endl;
			return 2;
		}
		int usedLocations[10];//initialyze an array that will hold which memory locations are being used now
		int *empty;// in order to know if we have something placed in that memory location, I need to check if it is not 0
		int isEmpty;
		int emptyCount=0;
		//do the same thing for all the 10 memory spaces
		empty = (int *) shmat(shm_id0, NULL, 0);//make empty be the value in the shared memory
		isEmpty = *empty;//set a variable to be the value and not the pointer to the memory
		usedLocations[0] = isEmpty;//use the array to store the shared memory value
		if(isEmpty == 0)//in case it is equal to 0, count how many empty spaces I have			
			emptyCount++;
			
		empty = (int *) shmat(shm_id1, NULL, 0);
		isEmpty = *empty;
		usedLocations[1] = isEmpty;
		if(isEmpty == 0)			
			emptyCount++;
			
		empty = (int *) shmat(shm_id2, NULL, 0);
		isEmpty = *empty;
		usedLocations[2] = isEmpty;
		if(isEmpty == 0)	
			emptyCount++;
			
		empty = (int *) shmat(shm_id3, NULL, 0);
		isEmpty = *empty;
		usedLocations[3] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
			
		empty = (int *) shmat(shm_id4, NULL, 0);
		isEmpty = *empty;
		usedLocations[4] = isEmpty;
		if(isEmpty == 0)		
			emptyCount++;
			
		empty = (int *) shmat(shm_id5, NULL, 0);
		isEmpty = *empty;
		usedLocations[5] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
			
		empty = (int *) shmat(shm_id6, NULL, 0);
		isEmpty = *empty;
		usedLocations[6] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
	
		empty = (int *) shmat(shm_id7, NULL, 0);
		isEmpty = *empty;
		usedLocations[7] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
			
		empty = (int *) shmat(shm_id8, NULL, 0);
		isEmpty = *empty;
		usedLocations[8] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
			
		empty = (int *) shmat(shm_id9, NULL, 0);
		isEmpty = *empty;
		usedLocations[9] = isEmpty;
		if(isEmpty == 0)
			emptyCount++;
	
		int readValue;//intialyze a variable that will hold the value read from the table
		//int randomSHM; Subistitute this Random value for a value that it is empty in the table
		//randomSHM = rand() %10;
		int *sharedValuePtr;//initialize a pointer that will hold the pointer to the shared location memory
		if(emptyCount<10)//if the empty count is smaller than 10, then there must be something in the table
		{
			int i=0;
			int spaceToPick=0;//initialize a variable that will tell from which space to pick from 
			for(i=0; i<10; i++)//do a loop and the first space that is not zero, is the one i will pick
			{	
				if(usedLocations[i]!=0)
				{	
					spaceToPick = i;
					i=10;//exit the loop
				}
			}
			//the following if statements will run only for the memory I should be picking at this moment 
			//they are all the same, besides the shared memory being changed
			if(spaceToPick ==0)//in case this is the place to pick from 
			{
				sharedValuePtr = (int *) shmat(shm_id0, NULL, 0);//point to the value that is in the table
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;//put this value in the read value
				*sharedValuePtr = 0;//set the shared memory to 0, since I just picked the value from it
			}
			if(spaceToPick ==1)
			{
				sharedValuePtr = (int *) shmat(shm_id1, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==2)
			{
				sharedValuePtr = (int *) shmat(shm_id2, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==3)
			{
				sharedValuePtr = (int *) shmat(shm_id3, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==4)
			{
				sharedValuePtr = (int *) shmat(shm_id4, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==5)
			{
				sharedValuePtr = (int *) shmat(shm_id5, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==6)
			{
				sharedValuePtr = (int *) shmat(shm_id6, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==7)
			{
				sharedValuePtr = (int *) shmat(shm_id7, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==8)
			{
				sharedValuePtr = (int *) shmat(shm_id8, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			if(spaceToPick ==9)
			{
				sharedValuePtr = (int *) shmat(shm_id9, NULL, 0);
				if(sharedValuePtr == (int *) -1)
				{
					cerr<<"shmat failed"<< endl;
					return 1;
				}
				readValue = *sharedValuePtr;
				*sharedValuePtr = 0;
			}
			//send a signal to the semaphore telling that I am done with this memory, and it can add another value
			//to the empty location
			semCommand[0].sem_num=0;
	  		semCommand[0].sem_op=1;
	  		semCommand[0].sem_flg=0;
	  		int semResult = semop(sem_id, semCommand, 1);
			if (semResult==-1)
			{
				cerr << "Unable to signal samaphore"  << endl;
				return 3;
			}
			cout << "You got gift " << readValue << " from the table"<<endl;
			int userChoice;
			cout<<"Would you like to try to pick another item from the table? Press 1 is so. "<<
				  "Otherwise, enter any number. ";
			cin>>userChoice;
			if(userChoice !=1);//if the user types 1, then the program can end
			else
				return 0;
		}
		else //wait semaphore, for the case that the table is currently empty
		{	//wait until someone sends a signal telling you that there is something in the table
			semCommand[0].sem_num=0;
	  		semCommand[0].sem_op=-1;
	  		semCommand[0].sem_flg=0;
	  		int semResult = semop(sem_id, semCommand, 1);
			if (semResult==-1)
			{
				cerr << "Unable to wait on samaphore"  << endl;
				return 2;
			}
		}
		emptyCount=0;//resets the empty count before running the while again
	}
	return 0;
}
