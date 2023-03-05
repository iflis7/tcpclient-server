#include "../include/socket.h"

void	connect_socket(char **argv)
{
	int					sendbytes;
	struct sockaddr_in	servaddr;
	char				sendline[MAXLINE];
	char				recvline[MAXLINE];

	int sockfd, n;
	/*
        Create a socket: 
            (Domain: AF_INET = Address Family-Internet)
            (Type: SOCK_STREAM = Stream Socket for TCP)
            (0 = For protocol in this car: TCP)
    */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("Error while creating the socket!", argv[0]);
	// Zero out the address
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	// Port: htons = "ost to network, short"
	servaddr.sin_port = htons(CLIENT_PORT); /* chat server */
											/*
        the inet_pton function, which converts a string representation of 
        an IPv4 address to a binary representation suitable for use by 
        network functions.
    */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_n_die("inet_pton error for %s ", argv[1]);
	// Connect to the server using the (connect) function
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_n_die("connect failed!");
	//We're connected. Prepare the message..
	// Send a GET command to the server
	sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
	sendbytes = strlen(sendline);
	// Writes the request to the socket
	if (write(sockfd, sendline, sendbytes) != sendbytes)
		err_n_die("write error");
	//Now read the server's response.
	while ((n = read(sockfd, recvline, MAXLINE - 1)) > 0)
	{
		printf("%s", recvline);
		memset(recvline, 0, MAXLINE);
	}
	if (n < 0)
		err_n_die("read error");
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		err_n_die("Usage: %s <server address>", argv[0]);

	connect_socket(argv);

	exit(0);
}