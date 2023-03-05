#ifndef SOCKET_H
# define SOCKET_H

# include <arpa/inet.h>
# include <errno.h>
# include <fcntl.h>
# include <netdb.h>
# include <signal.h>
# include <stdarg.h> /* for variadic function */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/socket.h> /* basic socket definitions */
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define CLIENT_PORT 80
# define SERVER_PORT 18000

# define MAXLINE 4096
# define SA struct sockaddr

// Utils
void	err_n_die(const char *fmt, ...);

// Client side
void	connect_socket(char **argv);
char	*bin2hex(const unsigned char *input, size_t len);

// Server side
void	launch_server(void);

#endif