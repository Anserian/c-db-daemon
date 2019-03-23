#include "server.h"
#include "jsonapi.h"

int listen_and_serve(char *endpoint, void *(*handler)(zsock_t *))
{
    zsock_t *server = zsock_new_rep(endpoint);

    handler(server);

    zsock_destroy(&server);

    return 0;
}

void *serve_database_interface(zsock_t *socket)
{
    char *initialization_request = zstr_recv(socket);

    parse_initialization_request(initialization_request);

    while (1)
    {
        char *string = zstr_recv(socket);

        zstr_send(socket, "Test");

        zstr_free(&string);
    }
}
