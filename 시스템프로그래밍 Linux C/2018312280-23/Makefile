all: client server
client: client.c
	gcc -o pa3_client client.c
server: server.c
	gcc -pthread -o pa3_server server.c

clean:
	rm pa3_client pa3_server