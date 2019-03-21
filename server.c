#include "server.h"

int listen_and_serve(char *endpoint)
{
    zsock_t *server = zsock_new_rep(endpoint);

    while (1)
    {
        char *string = zstr_recv(server);

        zstr_send(server, "Test");

        zstr_free(&string);
    }

    zsock_destroy(&server);
    return 0;
}
