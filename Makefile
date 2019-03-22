CC=gcc
CFLAGS=
OBJS=database.o utils.o sqlite.o server.o jsonapi.o cjson.o
BIN=db-daemon

db-daemon: $(OBJS)
	$(CC) $(CFLAGS) -o db-daemon index.c $(OBJS) -lsqlite3 -lzmq -lczmq

utils.o: utils.h
	$(CC) $(CFLAGS) -c -o utils.o utils.c

database.o: database.h
	$(CC) $(CFLAGS) -c -o database.o database.c

sqlite.o: sqlite.h
	$(CC) $(CFLAGS) -c -o sqlite.o sqlite.c

server.o: server.h
	$(CC) $(CFLAGS) -c -o server.o server.c

jsonapi.o: jsonapi.h
	$(CC) $(CFLAGS) -c -o jsonapi.o jsonapi.c

cjson.o: include/cJSON.h
	$(CC) $(CFLAGS) -c -o cjson.o include/cJSON.c

clean:
	rm $(OBJS) $(BIN)