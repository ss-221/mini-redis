#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define MAX_BACKLOG_QUEUE 5
#define MAX_BUFFER_SIZE 4096

#define EXIT_CODE "EXIT"

void PrintErrorMsg(const char* msg);

int InitServer(int port);

void ClientHandler(int clientSocket);

#endif SERVER_H