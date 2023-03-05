CC = gcc
CFLAGS = -g

COMMON_OBJS = utils.o 

all: $(COMMON_OBJS) tcpc tcps

utils.o:  utils/utils.c include/socket.h 
	$(CC) $(CFLAGS) -c utils/utils.c

tcpc: client/client.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcpc client/client.c $(COMMON_OBJS)

tcps: server/server.c $(COMMON_OBJS)
	$(CC) $(CFLAGS) -o tcps server/server.c $(COMMON_OBJS)

clean:
	rm -rf tcpc tcps *.o

