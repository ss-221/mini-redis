#include <server.h>

void PrintErrorMsg(const char* msg)
{
    printf("%s : %d\n", msg, errno);
}

int InitServer(int port)
{
    int socketID = socket(AF_INET, SOCK_STREAM, 0);

    if(socketID < 0)
    {
        PrintErrorMsg("Socket creation failed");
        return EXIT_FAILURE;
    }

    struct sockaddr_in socketAddress;

    socketAddress.sin_addr.s_addr = INADDR_ANY;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(port);

    if(bind(socketID, (struct sockaddr *) (&socketAddress), sizeof(socketAddress)) < 0)
    {
        PrintErrorMsg("Binding failed");
        return EXIT_FAILURE;
    }

    if(listen(socketID, MAX_BACKLOG_QUEUE) < 0)
    {
        PrintErrorMsg("Listening failed");
        return EXIT_FAILURE;
    }

    printf("Server started sucessfully on port %d\n", port);
    while(1)
    {
        int incomingSocket = 0;
        struct sockaddr_in clientAddress;
        socklen_t clientAddrSize = sizeof(clientAddress);
        incomingSocket = accept(socketID, (struct sockaddr *) (&clientAddress), &clientAddrSize);

        if(incomingSocket < 0)
        {
            PrintErrorMsg("Failed to accept the incoming request");
        }

        char msgBuffer[MAX_BUFFER_SIZE] = {0};

        int readRetVal = 0;

        while((readRetVal = read(incomingSocket, msgBuffer, MAX_BUFFER_SIZE)) > 0)
        {
            if(msgBuffer[MAX_BUFFER_SIZE - 1] != 0)
            {
                printf("Message too long: %d\nWill exit\n", readRetVal);
                strcpy(msgBuffer, EXIT_CODE);
            }
            else
            {
                msgBuffer[readRetVal] = 0;
                printf("Message received: %s\n", msgBuffer);
                fflush(stdout);
            }

            if(strcmp(msgBuffer, EXIT_CODE) == 0)
            {
                printf("EXIT received, closing the server.\n");
                close(incomingSocket);
                close(socketID);
                return EXIT_SUCCESS;
            }
        }
        
    }

    close(socketID);
    return EXIT_SUCCESS;

}