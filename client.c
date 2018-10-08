#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "tcp://127.0.0.1:3456"
#define BUFSZ sizeof(int64_t)

void fatal(const char *func)
{
    fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
    exit(1);
}

int main(const int argc, const char *argv[])
{
    char buf[BUFSZ] = { 0 };

    int sock;
    if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
        fatal("nn_socket");
    }

    if (nn_connect(sock, URL) < 0) {
        fatal("nn_connect");
    }

    for (int i = 0; i < 10; i++) {
        printf("C send %d\n", i);
        buf[0] = i;
        if (nn_send(sock, buf, BUFSZ, 0) < 0) {
            fatal("nn_send");
        }
        memset(buf, 0, BUFSZ);
        if (nn_recv(sock, buf, BUFSZ, 0) < 0) {
            fatal("nn_recv");
        }
        printf("C recv %d\n", (int)buf[0]);
    }

    return nn_shutdown(sock, 0);
}
