/*
==================================================
HEADERS
==================================================
*/
#include "nou_socket.h"

/*
==================================================
MAIN
==================================================
*/
int main(int argc, char **argv) {
    // ~ Testing: create a nou socket
    nou_socket *sockpg = nou_socket_create();

    // ~ Testing: fill out hints
    fill_out_hints(sockpg);

    // ~ Testing: open socket
    open_socket(sockpg);

    // ~ Testing: close socket
    close_socket(sockpg);
}

