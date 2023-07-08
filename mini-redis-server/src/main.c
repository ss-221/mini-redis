#include <server.h>

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Please call mini-redis-server with a port.\nEx: mini-redis-server 8080\n");
        return 0;
    }

    if(InitServer(atoi(argv[1])) == EXIT_FAILURE)
    {
        printf("Failed to start the server. Exiting.\n");
        return EXIT_FAILURE;
    }

    return 0;
}