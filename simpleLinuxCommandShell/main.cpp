/*
Henrique Medeiros Dos Reis
sep 27 2020 version
project 1 CSC35500 
*/
#include <iostream>
#include <csignal>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include "Command.h"
#include "Token.h"
#include "TokenStream.h"


 #define MAX_ARGS 100
 static int mySize;//variable that will hold the size of the current command
 static int myKid;//variable that will tell weather this is my kid or not
 static char* command[MAX_ARGS];//variable that will hold the command args
 /*
 	Method that will handle with the signals sent by the forked processes 
 */
 void myHandler(int sigVal)
{
	if(myKid==0)//if this kid is mine and was being ran in the background
	{	
		//print to the screen that the process was completed, and its information
		cout<<"Completed: PID="<<getpid()<<" : ";
		for(int i=0; i<mySize; i++)
			cout<<command[i]<<" ";
		cout<<endl;
		//set the kid to a number different than 0, to make sure it will not be printed more than once
		// for each background process
		myKid++;
	}
}
/*
	main method, it will run a simple shell that works in UNIX systems, it simulates the command prompt 
*/
int main(void)
{
	myKid=1;//set kid to be 1, since there is not kids yet
    Command com;// creates a command object that will hold the current command that needs to be processed
    
    // prompt for and read in first command. 
    cout << ">>>> ";
    com.read();
    mySize = com.numArgs();
    for(int i=0; i<com.numArgs();i++)//runs through the command arguments
	{	//set the static variable equal to the same elements in the command
		command[i] = const_cast<char*>(com.args()[i].c_str());
	}
	//sends a signal every time that the child has completed its process
	signal(SIGCHLD, myHandler);
	//keep going until the user types exit
    while(com.name()!="exit")
    {	
    	//create a pipe that will be use to intercommunicate between two processes 
    	int pipeInfo[2];
		int myPipe = pipe(pipeInfo);
    	if(com.name()=="cd")//check if the user wants to change directory 
		{
			string myNewDir;//create a string that will hold the directory name and path 
			for(int i=1; i<com.numArgs();i++) //loop through the command arguments 
			{
				myNewDir += com.args()[i];//set the myNewDir to the arguments in the command
			}
			chdir(myNewDir.c_str());//change the directory to the path wanted
		}
		else if(com.name()=="exit")//in case the user types "exit" quit running 
			return 0;
		else//in case the user types a different argument from the previous ones.
		{	
			int size = com.numArgs();//size variable that will hold the size of the command in an integer value
			char* args[size];//create an array of char of the size of the command
			for(int i=0; i<com.numArgs();i++)//make the array previously created equal to the command 
			{
				args[i] = const_cast<char*>(com.args()[i].c_str());
				args[i+1]=NULL;//sets the last piece to NULL so it can be used in the execvp method
			}
			int pid=fork();//create a integer variable and fork it so it can be used to run multiple processes
			if(pid!=0)//we are the "parent"
			{	
				if(!com.backgrounded())// in case the command was not backgrounded
				{	
					waitpid(pid, NULL, 0);//wait until the child process is over
				}
				if(com.backgrounded())//in case the command was backgrounded 
					myKid=0;//sets its child to 0, because it will need to be used in the future to tell that it completed
				if(com.pipeOut())//in case the command has a pipe
				{
					close(pipeInfo[1]);//first, close the pipe that would write 
					dup2(pipeInfo[0], fileno(stdin));// then change the source where it would get the input
					for(int i=0; i<com.numArgs();i++)//loop through the command and set the args equal to that
					{
						args[i] = const_cast<char*>(com.args()[i].c_str());
						args[i+1]=NULL;//the last piece needs to be null
					}
				}
			}
			else//we are the "child
			{	
			
				if(com.name()=="exit")//in case the user types "exit" quit running 
					return 0;
				int size = com.numArgs();//size variable that will hold the size of the command in an integer value
				char* args[size];//create an array of char of the size of the command
				for(int i=0; i<com.numArgs();i++)//make the array previously created equal to the command 
				{
					args[i] = const_cast<char*>(com.args()[i].c_str());
					args[i+1]=NULL;//sets the last piece to NULL so it can be used in the execvp method
				}
				if(com.redirIn()) // in case the file input needs to be redirected
				{
					FILE *fp = fopen(com.inputRedirectFile().c_str(),"r");//open a file in the read mode
					dup2(fileno(fp), fileno(stdin));//change the input to be the file that we just opened
				}
				if(com.redirOut())// in case the file output needs to be redirected
				{
					FILE *fp = fopen(com.outputRedirectFile().c_str(),"w");//open a file in the write mode
					dup2(fileno(fp), fileno(stdout));//change the output to be the file that we just opened
				}
				if(com.pipeOut())//in case we had a pipe process, this is the second part of it
				{
					close(pipeInfo[0]);//close the read part of the file, since we will just give outputs
					dup2(pipeInfo[1], fileno(stdout));//change its output to be the pipe
					for(int i=0; i<com.numArgs();i++)//make the array previously created equal to the command 
					{
						args[i] = const_cast<char*>(com.args()[i].c_str());
						args[i+1]=NULL;//sets the last piece to NULL so it can be used in the execvp method
					}
				}
				
				
				execvp(args[0], args);//execute the command
				
				//send a message in case the command was not executed
				cout<<"The command could not be executed, check the input"<< endl;
			}
		}
		if(com.name()=="exit")//in case the user types "exit" quit running 
			return 0;
		// prompt for and read next command	
		cout << ">>>> ";
		//read the next command
		com.read();
		for(int i=0; i<com.numArgs();i++)//loop through the command
		{
			command[i] = const_cast<char*>(com.args()[i].c_str());//update the command static variable
		}
		mySize = com.numArgs();//update the static variable that holds the command size
    }
    cout << "Thank you for using MedeirosDosReis-shell. We now return you to your regularly scheduled shell!" << endl;
    return 0;
}
