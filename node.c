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
char Node1_IP [50];
char Node2_IP [50];
char Node3_IP [50];

int main()
{
    int args;
    do
    {
        printf("Enter your IP");
    }while(( args = scanf("%50s", Node1_IP)) == 0)
    
    do
    {
        printf("Enter IPof second Node");
    }while(( args = scanf("%50s", Node1_IP)) == 0)
}

