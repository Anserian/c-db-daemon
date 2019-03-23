#ifndef DATABASE_ZMQ_SERVER
#define DATABASE_ZMQ_SERVER

#include <czmq.h>
#include <stdio.h>

int listen_and_serve(char *endpoint, void *(*)(zsock_t *));

void *serve_database_interface(zsock_t *);

#endif
