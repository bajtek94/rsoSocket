#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<signal.h>
#include<unistd.h>
#include<math.h>
#include <ctime>

#include "functions.h"

using namespace std;

#define PORT 9735
#define SERVER_IP "127.0.0.1"

int main() {

	socklen_t serverLen, clientLen;
	struct sockaddr_in serverAddress, clientAddress;
	int socketClient, socketServer;

	socketServer = socket(AF_INET, SOCK_STREAM, 0);

	printf("Server > started\n");

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT);
	serverLen = sizeof(serverAddress);
	bind(socketServer, (struct sockaddr *) &serverAddress, serverLen);

	listen(socketServer, 5);

	while (1) {
		printf("Server > waiting...\n");

		int taskCode;
		int requestID;
		double num;
		clientLen = sizeof(clientAddress);
		socketClient = accept(socketServer, (struct sockaddr *) &clientAddress, &clientLen);
		printf("Server > client has connected\n");
		//int numToCheck = 0;
		bool isLittle = true;
		//read(socketClient, &numToCheck, sizeof(int));
		//printf("Otrzymana liczba: %d\n", numToCheck);
		if (isLittleEndian()) {
			printf("Server is Little-Endian system\n");
			isLittle = true;
		}
		else {
			printf("Server is Big-Endian system\n");
			isLittle = false;
		}
		while (1) {
			read(socketClient, &taskCode, sizeof(int));
			if (isLittle == false) { taskCode = changeEndian(taskCode); }
			printf("Server > client sent task code: %d\n", taskCode);
			read(socketClient, &requestID, sizeof(int));
			if (isLittle == false) { requestID = changeEndian(requestID); }
			printf("Server > client sent request ID: %d\n", requestID);
			if (taskCode == 1) {
				read(socketClient, &num, sizeof(double));
				if (isLittle == false) { num = changeEndian(num); }
				printf("Server > client sent this number: %f\n", num);
				num = sqrt(num);
				if (isLittle == false) { num = changeEndian(num); }
				write(socketClient, &num, sizeof(double));
				printf("Server > Root has sent to client\n\n");
			}
			else if (taskCode == 2) {
				time_t actualTime = time(0);
				if (isLittle == false) { actualTime = changeEndian(actualTime); }
				write(socketClient, &actualTime, sizeof(time_t));
			}
			else {
				printf("Unrecognized task code: %d", taskCode);
			}
			//time_t actualTime = time(0);
			//write(socketClient, &actualTime, 1);
			//cout << asctime(localtime(&result))
			//        << result << " seconds since the Epoch\n";

			//write(socketClient

		}
		close(socketClient);

	}



	return 0;
}




/// przesłanie liczby na serwer,

/// serwer odsyła pierwiastek z tej liczby i podaje czas na serwerze

/// oparte na protokole TCP
/// BigEndian