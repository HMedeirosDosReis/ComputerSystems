// FILE:  server.cpp
// AUTHOR: Henrique Medeiros Dos Reis
// DATE:    4/27/2021
//
// A simple iterative server program that utilizes Unix sockets and returns or not the value in the accumulator, based in the
// each connecting client's command sent
#include <arpa/inet.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;


// various error codes that correspond to socket problems
#define SUCCESS 0
#define USAGE_ERROR 1
#define SOCK_ERROR 2
#define BIND_ERROR 3
#define LISTEN_ERROR 4
#define READ_ERROR 5


// limits the number of clients that can be waiting to connect to the server
#define MAX_WAITING 25

// forward definition of the actual server code
int do_server(unsigned int on_port);

// do the actual serving of the data, given a client
void do_work(int with_sock, struct sockaddr_in *from_cli);
int accumulator;

int main(int argc, char *argv[])
{
	accumulator=0;
  	// check to make sure program has been invoked properly
  	if (argc!=2)
    {
      	cout << "Usage: " << argv[0] << " <port number>" << endl;
      	exit (USAGE_ERROR);
    }
  	// invoke server code
  	return do_server(atoi(argv[1]));
}

//this method initializes the server, which keeps reading the commands sent by clients 
int do_server(unsigned int on_port)
{
	// the listening socket
  	int listen_sock;

  	//The sockaddr_in specifies the address of the socket
  	//for TCP/IP sockets.
  	struct sockaddr_in local_addr;

  	//the socket() function creates our listening socket
  	listen_sock=socket(AF_INET,SOCK_STREAM,0);
    
  	//If the socket() function fails we exit
  	if(listen_sock<0)
    {
      	cout << "Could not create listening socket!" << endl;
      	return SOCK_ERROR;
    }

  	// Fill in local (server) half of socket info
  	local_addr.sin_family=AF_INET;         //IPv4 Address family
  	local_addr.sin_addr.s_addr=INADDR_ANY; //Wild card IP address
 	local_addr.sin_port=htons(on_port);    //port to use

  	// bind (i.e. "fill in") our socket info to our socket
  	if(bind(listen_sock,(sockaddr*)&local_addr,sizeof(local_addr))!=0)
    {
      	cout << "Binding failed - this could be caused by:" << endl
	   	<< "  * an invalid port (no access, or already in use?)" << endl
	   	<< "  * an invalid local address (did you use the wildcard?)" 
	  	<< endl;
      	return BIND_ERROR;
    }

  	//listen for a client connection on 
  	if(listen(listen_sock,MAX_WAITING)!=0)
    {
      	cout << "Listen error" << endl;
      	return LISTEN_ERROR;
    }
  
  	while(true)//keep handling connections forever
    {
      	int connected_sock;      // socket for the actual connected client
      	struct sockaddr_in from; // holds client address data
      	unsigned int from_len;   // holds size of client address data
      
      	// really only needed for windows, but doesn't break things here ... 
      	from_len=sizeof(from);
      
      	// wait for the listening socket to get an attempted
      	//   client connection
      	connected_sock=accept(listen_sock,
			    (struct sockaddr*)&from,
			    &from_len);
      
      	// get and process attempted client connection
      	do_work(connected_sock, &from);
  }
  	// if we get here, things worked just fine. But we should never get here!
  	return SUCCESS;
}


// this is the actual method that handles the commands
void do_work(int connsock, struct sockaddr_in *client_addr)
{
	//initialize the used variables 
  	string buffer;
  	int nRead;
  	char buff[81];
  	nRead=read(connsock, buff, 80);//try to read from the client 
  	if(nRead<0)//if it is less than 0, send the error 
  	{
		cout << "read() error" << endl;
      	exit(READ_ERROR);
  	}
  
  	char *cbuff=(char *)buffer.c_str();
  	string stripC="";//string that will represent the command
  	int numberStart;//int of where the integer will start
  	string stripInt="";//string that will hold the integer in the command
  	int shouldWrite;
	for(int i=0; i<81;i++)//loop through the the buff char array
	{
		if(!buff[i])//if im in a null position, stop this loop 
			i=81;
		else if(buff[i]!=' ')//if this is not a space, go ahead and put this into the stripC
			stripC+=buff[i];
		else
		{//since i was not null and wasnt a space, it means that im a space, which means that we have more from the command
			numberStart=i+1;//start from the next slot the continued command 
			i=81;//quit the loop
		}
	}
	
	if(stripC=="add")//in case the command was add
	{
		for(int i=numberStart;i<81;i++)//go ahead and deal with the rest of the command, which is just a number
		{
			if(buff[i]!=' ')//if this is not a space, go ahead and put this into the stripInt
				stripInt+=buff[i];
			else
				i=81;
		}
		accumulator+=atoi(stripInt.c_str());//go ahead and transform my stripInt to an integer
		shouldWrite=1;//let the program know that it should print the accumulator later
	}
	else if(stripC=="clear")//in case the command is clear
	{
		accumulator=0;//set the accumulator to 0
		shouldWrite=0;//we shouldnt print anything now
	}
	else if(stripC=="get")//in case the command is get 
	{
		shouldWrite=1;//just let the program know that it should print
	}
  	// make a local log of who connected ...  HELPS DEBBUGING
  	cout << "Connection from " << inet_ntoa(client_addr->sin_addr) <<" message: "<<buff<< endl;
  	cout << "stripped command = " <<stripC<<" Stripped int "<<stripInt<<"acc" <<accumulator <<endl;
  	//close the client socket
	buffer="";//initialize the buffer that will be sent to the client
	buffer+=to_string(accumulator);//make the accumulator a string and add to the buffer
 	buffer+='\n';//make sure to terminate in a new line
	if(shouldWrite==1)//if we need to print this time, go ahead and deal with  it
	{
		int needed=buffer.length();
		while(needed)  // as long as writing is not yet completed, 
		{ 
			// keep writing more of the buffer
			int n=write(connsock, cbuff, needed);
			needed-=n;//decrement needed 
			cbuff+=n;//go to the next slot
		}	
	}
  	close(connsock);
}

