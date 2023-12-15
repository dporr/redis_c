#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <regex.h>     

/* Parses a line in the form *N\r\n$M\r\nABC...M\r\nEOF
returns an array of N elements containing the command and its arguments
ie. 
*1\r\n$4\r\nping\r\n
["PING"]
*/
// char* parse_line(char* command){
// 	char* cmd;
// 	int c;
// 	for(int i=0; c != 'EOF'; i++)

// 	return cmd;
// }

// void handle_PING(char* arguments,char* reply){
// }

int main() {
	// Disable output buffering
	//setbuf(stdout, NULL);

	// You can use print statements as follows for debugging, they'll be visible when running tests.
	printf("Logs from your program will appear here!\n");

	int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	//Since the tester restarts your program quite often, setting REUSE_PORT
	//ensures that we don't run into 'Address already in use' errors
	int reuse = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
		printf("SO_REUSEPORT failed: %s \n", strerror(errno));
		return 1;
	}
	// int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	struct sockaddr_in  srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port   = htons(6379);
	struct in_addr target_address;
	memset(&target_address,0, sizeof(struct in_addr));
	target_address.s_addr =   htonl(INADDR_ANY);
	//Can we do srv_addr.sin_addr.s_addr =  htonl(INADDR_ANY); directly?
	srv_addr.sin_addr 	  =  target_address;

	bind(socket_fd, (struct sockaddr *) &srv_addr, sizeof(srv_addr)); 
	listen(socket_fd, 50);
	uint32_t client_fd = accept(socket_fd,0,0);
	uint32_t REQUEST_SIZE = 4096;
	char* request[REQUEST_SIZE];
	memset(&request, 0, REQUEST_SIZE * sizeof(char));
	if(client_fd) recv(client_fd, &request, REQUEST_SIZE, 0 );
	printf("%s", &request); //FIX: This generates a warning
	char* response = "+PONG\r\n";
	send(client_fd, response,strlen(response),0);
	// Uncomment this block to pass the first stage
	//
	// int server_fd, client_addr_len;
	// struct sockaddr_in client_addr;
	//
	// server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// if (server_fd == -1) {
	// 	printf("Socket creation failed: %s...\n", strerror(errno));
	// 	return 1;
	// }
	//
	//
	// struct sockaddr_in serv_addr = { .sin_family = AF_INET ,
	// 								 .sin_port = htons(6379),
	// 								 .sin_addr = { htonl(INADDR_ANY) },
	// 								};
	//
	// if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != 0) {
	// 	printf("Bind failed: %s \n", strerror(errno));
	// 	return 1;
	// }
	//
	// int connection_backlog = 5;
	// if (listen(server_fd, connection_backlog) != 0) {
	// 	printf("Listen failed: %s \n", strerror(errno));
	// 	return 1;
	// }
	//
	// printf("Waiting for a client to connect...\n");
	// client_addr_len = sizeof(client_addr);
	//
	// accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_len);
	// printf("Client connected\n");
	//
	//close(socket_fd);

	return 0;
}
