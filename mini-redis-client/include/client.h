#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 4096
#define EXIT_CODE "EXIT"

void PrintErrorMsg(const char* msg);

int InitClient(int port);