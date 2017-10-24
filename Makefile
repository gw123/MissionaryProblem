all: server client
LIBS = -lpthread -L/data/install/libevent/lib -levent

INCLUDE = -I/data/install/libevent/include

server:  base_tcp.c util.o
	gcc -o $@   util.o base_tcp.c  $(LIBS) $(INCLUDE)

client: base_client.c util.o
	gcc -o $@  base_client.c util.o $(LIBS) $(INCLUDE)

util.o: util.c
	gcc  -c util.c

buffer.o: buffer.c
	gcc -c  buffer.c

clean:
	rm ./output/server ./output/client
	echo 'clean success'
install:
	mv  server ./output/server
	mv  client ./output/client
	rm util.o
	echo 'install success'
