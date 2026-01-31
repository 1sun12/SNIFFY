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

    // ~ Testing: destroy a nou socket
    nou_socket_destroy(sockpg);
}

