#include <client.h>

void PrintErrorMsg(const char* msg)
{
    printf("%s : %d\n", msg, errno);
}

int InitClient(int port)
{
    int socketID = socket(AF_INET, SOCK_STREAM, 0);

    if(socketID < 0)
    {
        PrintErrorMsg("Socket creation failed");
        return EXIT_FAILURE;
    }

    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);   

    if(inet_pton(AF_INET, "localhost", &serverAddress.sin_addr) < 0)
    {
        PrintErrorMsg("Failed to convert the address");
        return EXIT_FAILURE;
    }

    if(connect(socketID, (struct sockaddr *) (&serverAddress), sizeof(serverAddress)) < 0)
    {
        PrintErrorMsg("Failed to connect to the server");
        return EXIT_FAILURE;
    }

    else
    {
        printf("Successfully connected to the server\n");
    }

    char* msgBuffer = malloc(MAX_BUFFER_SIZE);

    while(fgets(msgBuffer, MAX_BUFFER_SIZE, stdin) > 0)
    {
        msgBuffer[strcspn(msgBuffer, "\n")] = 0;
        if(send(socketID, msgBuffer, strlen(msgBuffer), 0) < 0)
        {
            printf("Failed to send");
        }

        if(strcmp(msgBuffer, EXIT_CODE) == 0)
        {
            printf("Received EXIT.");
            free(msgBuffer);
            break;
        }
    }

    return EXIT_SUCCESS;

}