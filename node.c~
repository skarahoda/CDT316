#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/times.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/signal.h>
#include <fcntl.h>

#define messageLength 100

typedef struct frame {
        int flagg;
        int seq;
        int ack;
        int win_size;
        int crc;
        int has_data;
        char data[100];
} frame;

char node1_IP [50];
char node2_IP [50];
char node3_IP [50];
int port1;
int port2;
int socReceiver2;
int sockSender3;

void input();
void sender();
void *receiver(void *arg);

void input()
{
	int args;
	printf("Enter your IP:");
	if(( args = scanf("%50s", node1_IP)) == 0)
	{
		printf("\nPlease enter a valid input!\n");
		exit(EXIT_FAILURE);
	}
		
	printf("\nEnter IP of second node:");
	if(( args = scanf("%50s", node2_IP)) == 0)	
	{
		printf("\nPlease enter a valid input!\n");
		exit(EXIT_FAILURE);
	}
	
	printf("\nEnter port for communication of second node:");
	if(( args = scanf("%d", &port1)) == 0)
	{
		printf("\nPlease enter a number!\n");
		exit(EXIT_FAILURE);
	}

	printf("\nEnter IP of third node:");
	if(( args = scanf("%50s", node3_IP)) == 0)
	{
		printf("\nPlease enter a valid input!\n");
		exit(EXIT_FAILURE);
	}

	printf("\nEnter port for communication of third node:");
	if(( args = scanf("%d", &port2)) == 0)
	{
		printf("\nPlease enter a number!\n");
		exit(EXIT_FAILURE);
	}
	if(abs(port1-port2) == 1)
	{
		printf("\nPort numbers are consecutive.Please enter different port numbers!\n");
		exit(EXIT_FAILURE);
	}
}

void *receiver(void *arg)
{
	struct hostent *nodeOtherInfo;
	struct hostent *node1Info;
	struct sockaddr_in node1;
	struct sockaddr_in nodeOther;
	int sock;
	char *str;
	int port;
	str=(char*)arg;
	char node_IP [50];
	
	int nOfBytes;
	char messageString[messageLength];
	frame frm;
	
	//get the information of other node
	if(str == "0")
	{
		port=port1;
		strcpy(node_IP, node2_IP);
	}
	else
	{
		port=port2;
		strcpy(node_IP, node3_IP);
	}
	
	//Create socket
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("Could not create a socket\n");
		exit(1);
	}
	
	// Make sock non-blocking
	fcntl(sock,F_SETFL,O_NONBLOCK);
	
	// Fix the nodeOther struct
	nodeOther.sin_family = AF_INET;
	nodeOther.sin_port = htons(port);
	nodeOtherInfo = gethostbyname(node_IP);
	if (nodeOtherInfo == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node_IP);
		exit(1);
	}
	nodeOther.sin_addr = *(struct in_addr *)nodeOtherInfo->h_addr;
	
	// Fix node1 struct
	node1.sin_family = AF_INET;
	node1.sin_port = htons(port+1);
	node1Info = gethostbyname(node1_IP);
	if (node1Info == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node1_IP);
		exit(1);
	}
	node1.sin_addr = *(struct in_addr *)node1Info->h_addr;
	//node1.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sock, (struct sockaddr *)&node1, sizeof(struct sockaddr)) == -1)
	{
		printf("Failure when attempt to bind to node:%s\n",node_IP);
		exit(1);
	}
	printf("receiver is done. Node IP:%s\n",node_IP);
	while (1) 
	{
		nOfBytes = recvfrom(sock, &frm, sizeof(frame), 0, NULL, NULL);
		if (nOfBytes > 0)
		{
			printf("Received from %s: %s\n>",node_IP, frm.data);
			fflush(stdout);
		}
	}
}

void sender()
{
	struct hostent *node1_2Info; 
	struct hostent *node1_3Info;
	struct hostent *node2Info;
	struct hostent *node3Info;
	struct sockaddr_in node1_2;
	struct sockaddr_in node1_3;
	struct sockaddr_in node2;
	struct sockaddr_in node3;
	int sock1, sock2;
	
	int nOfBytes;
	char messageString[messageLength];
	frame frm;
	
	//Create sockets
	sock1 = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock1 < 0) {
		perror("Could not create a socket\n");
		exit(1);
	}
	sock2 = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock2 < 0) {
		perror("Could not create a socket\n");
		exit(1);
	}
	
	// Make sock non-blocking
	fcntl(sock1,F_SETFL,O_NONBLOCK);
	fcntl(sock2,F_SETFL,O_NONBLOCK);
	
	// Fix the node2 struct
	node2.sin_family = AF_INET;
	node2.sin_port = htons(port1+1);
	node2Info = gethostbyname(node2_IP);
	if (node2Info == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node2_IP);
		exit(1);
	}
	node2.sin_addr = *(struct in_addr *)node2Info->h_addr;
	
	// Fix the node3 struct
	node3.sin_family = AF_INET;
	node3.sin_port = htons(port2+1);
	node3Info = gethostbyname(node3_IP);
	if (node3Info == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node3_IP);
		exit(1);
	}
	node3.sin_addr = *(struct in_addr *)node2Info->h_addr;
	
	// Fix node1_2 struct
	node1_2.sin_family = AF_INET;
	node1_2.sin_port = htons(port1);
	node1_2Info = gethostbyname(node1_IP);
	if (node1_2Info == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node1_IP);
		exit(1);
	}
	node1_2.sin_addr = *(struct in_addr *)node1_2Info->h_addr;
	//node1.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sock1, (struct sockaddr *)&node1_2, sizeof(struct sockaddr)) == -1)
	{
		printf("Failure when attempt to bind 1\n");
		exit(1);
	}
	
	// Fix node1_3 struct
	node1_3.sin_family = AF_INET;
	node1_3.sin_port = htons(port2);
	node1_3Info = gethostbyname(node1_IP);
	if (node1_3Info == NULL) 
	{
		fprintf(stderr, "initSocketAddress - Unknown host %s\n", node1_IP);
		exit(1);
	}
	node1_3.sin_addr = *(struct in_addr *)node1_3Info->h_addr;
	//node1.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(sock2, (struct sockaddr *)&node1_3, sizeof(struct sockaddr)) == -1)
	{
		printf("Failure when attempt to bind 2\n");
		exit(1);
	}
	while(1) 
	{
		printf("\n>");
		fgets(messageString, messageLength, stdin);
		messageString[messageLength - 1] = '\0';
		if(strncmp(messageString,"quit\n",messageLength) != 0)
		{
			strcpy(frm.data, messageString);
			nOfBytes = sendto(sock1, &frm, sizeof(frm), 0, (struct sockaddr *)&node2, sizeof(struct sockaddr));
			if (nOfBytes < 0) 
			{
				perror("Could not write data\n");
        			exit(1);
    			}
    			nOfBytes = sendto(sock2, &frm, sizeof(frm), 0, (struct sockaddr *)&node3, sizeof(struct sockaddr));
			if (nOfBytes < 0) 
			{
				perror("Could not write data\n");
        			exit(1);
    			}
    		}
    		else 
    		{
    			close(sock1);
    			close(sock2);
    			exit(1);
		}
	}
}
void main()
{
	pthread_t tID1;
	pthread_t tID2;
	input();
	char buffer[50];
	pthread_create(&tID1,NULL,receiver,"0");
	pthread_create(&tID2,NULL,receiver,"1");
	sender();
}
