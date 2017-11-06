all: server client
LIBEVENT = -lpthread -L/data/install/libevent/lib -levent
LIBS = -lpthread 
INCLUDE = -I/data/install/libevent/include

server:  base_tcp.c util.o buffer.o http_help.o net.o
	gcc -o $@   base_tcp.c util.o buffer.o  http_help.o net.o $(LIBS) $(INCLUDE)

client: base_client.c util.o buffer.o http_help.o net.o
	gcc -o $@   base_client.c http_help.o util.o buffer.o  net.o $(LIBS) $(INCLUDE)

util.o: util.c
	gcc  -c util.c

buffer.o: buffer.c
	gcc -c  buffer.c

http_help.o:
	gcc -c http_help.c

net.o:
	gcc -c net.c

clean:
	rm *.o
	echo 'clean success'
install:
	mv  server ./output/server
	mv  client ./output/client
	echo 'install success'
