#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

// man 7 ip
// man 2 bind
// man hto
// man listen
// man accept
// man 2 send
// man close

int main(int argc, char **argv)
{ 
	// create socket info structure
	struct sockaddr_in server_info = {0};

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(1337);
	
	socklen_t server_info_len = sizeof(server_info);
	
	struct sockaddr client_info = {0};
	socklen_t client_info_len = sizeof(client_info);

	// create tcp_socket
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sfd ) { 
		perror("unable to create a new socket");
		return -1;
	}

	// bind
	if (0 > bind(sfd, (struct sockaddr*)&server_info, server_info_len)) { 
		perror("unable to bind socket");
		return -1;
	};

	// listen
	if (0 > listen(sfd, 0)) { 
		perror("unable to listen");
		return -1;
	}

	// accept
	int cfd= accept(sfd, &client_info, &client_info_len);

	if (0 > cfd)  { 
		perror("unable to accept client");
		return -1;
	}


	char *msg = "hello\n";
	ssize_t sent = send(cfd, (void *)msg, strlen(msg), 0);

	printf("ok");
	close(cfd);
	
	return 0;
}
