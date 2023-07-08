#include <client.h>

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Please call mini-redis-client with a port.\nEx: mini-redis-client 8080\n");
        return 0;
    }

    if(InitClient(atoi(argv[1])) == EXIT_FAILURE)
    {
        printf("Failed to start the client. Exiting.\n");
        return EXIT_FAILURE;
    }

    return 0;
}