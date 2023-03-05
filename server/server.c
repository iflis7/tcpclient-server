#include "../include/socket.h"

void	launch_server(void)
{
	struct sockaddr_in	servaddr;
	uint8_t				buff[MAXLINE + 1];
	uint8_t				recvline[MAXLINE + 1];
	struct sockaddr_in	addr;
	socklen_t			addr_len;

	int listenfd, connfd, n;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("socket error.");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);
	// Listen and Bind
	if ((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
		err_n_die("bind error.");
	if ((listen(listenfd, 10)) < 0)
		err_n_die("listen error.");
	for (;;)
	{
		//accept blocks until an incoming connection arrives
		//it returns a "file descriptor" to the connection
		printf("waiting for a connection on port %d\n", SERVER_PORT);
		fflush(stdout);
		connfd = accept(listenfd, (SA *)NULL, NULL);
		memset(recvline, 0, MAXLINE);
		//Now read the client's message.
		while ((n = read(connfd, recvline, MAXLINE - 1)) > 0)
		{
			fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);
			//hacky way to detect the end of the message.
			if (recvline[n - 1] = '\n')
			{
				break ;
			}
			memset(recvline, 0, MAXLINE);
		}
		if (n < 0)
			err_n_die("read error!");
		snprintf((char *)buff, sizeof(buff),
				"HTTP/1.0 200 OK\r\n\r\nAzul Dina!");
		write(connfd, (char *)buff, strlen((char *)buff));
		close(connfd);
	}
}

int	main(int argc, char **argv)
{
	// if (argc != 2)
	// 	err_n_die("Usage: %s <server address>", argv[0]);

	launch_server();

	exit(0);
}