#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <string> 

bool isLittleEndian();


using namespace std;

#define PORT 9735
#define SERVER_IP "127.0.0.1"

int main() {
    srand( time( NULL ) );
    socklen_t len;
    struct sockaddr_in address;
    int result;
    double numberToSend = 36;
    time_t actualTimeFromServer;
    int socketC = socket(AF_INET, SOCK_STREAM, 0);
    
    
    printf("Client > started\n");
    int a = 1;
    char* b = (char*)&a;
    
    if(isLittleEndian()) {
      printf("this computer is in Little-Endian Architecture\n");
    }
    else {
      printf("this computer is in Big-Endian Architecture\n");
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(PORT);
    len = sizeof(address);
    
    result = connect(socketC, (struct sockaddr *) &address, len);
    
    if(result == -1) {
      perror("connection failed");
      exit(1);
    }
    else {
      printf("Client > connected with server\n");
      write(socketC, &a, sizeof(int));
      while(1) {
	int choice;
	int taskCode;
	int requestID;
	printf("\n1. Get root from number");
	printf("\n2. Get time from server");
	scanf("%d", &choice);
	switch(choice) {
	  case 1:
	    taskCode = choice;
	    requestID = (rand() % 99999999 ) + 1;
	    write(socketC, &taskCode, sizeof(int));
	    write(socketC, &requestID, sizeof(int));
	    write(socketC, &numberToSend, sizeof(double));
	    printf("Client > You sent number '%f' to server\n", numberToSend);
	    read(socketC,  &numberToSend, sizeof(double));
	    printf("Server > Root from this number is: %f\n\n", numberToSend);
	    
	    break;
	  case 2:
	    taskCode = choice;
	    requestID = (rand() % 99999999 ) + 1;
	    write(socketC, &taskCode, sizeof(int));
	    write(socketC, &requestID, sizeof(int));
	    read(socketC, &actualTimeFromServer, sizeof(time_t));
	    printf("Server > Actual time is: %s", asctime(localtime(&actualTimeFromServer)));
	    
	    break;
	}
      }
      close(socketC);
    }
  
    
    
    return 0;
}



bool isLittleEndian() {
  int a = 1;
  char* b = (char*)&a;
  if(*b == '0') {
    return false;
  }
  else {
    return true;
  }
}

