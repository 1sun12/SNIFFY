/*
==================================================
HEADERS
==================================================
*/
#include "debug.h"
#include "nou_socket.h"

/*
==================================================
MAIN
==================================================
*/
int main(int argc, char **argv) {
    OUTPUT_D_MSG("~ MAIN EXECUTION STARTING ~");

    // ~ Testing: create a nou socket
    nou_socket *sockpg = nou_socket_create();

    // ~ Testing: fill out hints
    fill_out_hints(sockpg);

    // ~ Testing: open socket
    open_socket(sockpg);

    // ~ Testing: recieve a frame
    recv_socket(sockpg);
}

