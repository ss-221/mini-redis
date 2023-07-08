SERVER_INCLUDE_DIR = -I./mini-redis-server/include
CLIENT_INCLUDE_DIR = -I/mini-redis-client/include

all: mini-redis-server mini-redis-client

mini-redis-server: mini-redis-server/src/main.c
	gcc mini-redis-server/src/main.c mini-redis-server/src/server.c -I./mini-redis-server/include -o build/mini-redis-server

mini-redis-client: mini-redis-client/src/main.c
	gcc mini-redis-client/src/main.c mini-redis-client/src/client.c -I./mini-redis-client/include -o build/mini-redis-client


clear:
	@echo "Clearing build folder"
	rm build/mini-redis-server build/mini-redis-client
	rm build/mini-redis-server build/mini-redis-server