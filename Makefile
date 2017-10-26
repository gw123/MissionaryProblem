all: server client
LIBS = -lpthread -L/data/install/libevent/lib -levent

INCLUDE = -I/data/install/libevent/include

server:  base_tcp.c util.o buffer.o http_help.o net.o
	gcc -o $@   base_tcp.c util.o buffer.o  http_help.o net.o $(LIBS) $(INCLUDE)

client: base_client.c util.o buffer.o http_help.o net.o
	gcc -o $@   base_client.c util.o buffer.o  net.o $(LIBS) $(INCLUDE)

util.o: util.c
	gcc  -c util.c

buffer.o: buffer.c
	gcc -c  buffer.c

http_help.o:
	gcc -c http_help.c

net.o:
	gcc -c net.c

clean:
	rm ./output/server ./output/client
	echo 'clean success'
install:
	mv  server ./output/server
	mv  client ./output/client
	rm util.o  buffer.o http_help.o net.o
	echo 'install success'
