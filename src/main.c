/*
==================================================
HEADERS
==================================================
*/
#include "debug.h"
#include "sock.h"
#include "eth.h"
#include "ip.h"
#include "tcp.h"

/*
==================================================
MAIN
==================================================
*/
int main(int argc, char **argv) {
    OUTPUT_D_MSG("~ MAIN EXECUTION STARTING ~");

    // ~ Testing: create a socket
    sock_t *s = sock_create();

    // ~ Testing: fill out hints
    s->fill_hints(s);

    // ~ Testing: open socket
    s->open(s);

    // ~ Testing: recieve a frame
    s->recv(s);

    // ~ Testing: create ethernet parser
    eth_t *e = eth_create();

    // ~ Testing: cast buffer to ethernet header
    e->set_buffer(e, s->buffer);

    // ~ Testing: convert ethernet header to something humanly readable
    e->parse(e);

    // ~ Testing: create ip parser
    ip_t *i = ip_create();

    // ~ Testing: set buffer for ip parser
    i->set_buffer(i, s->buffer);

    // ~ Testing: parse the source IP
    i->parse_src(i);

    // ~ Testing: parse the destination IP
    i->parse_dst(i);

    printf("\nSource MAC: %s", e->src_mac);
    printf("\nDestination MAC: %s", e->dst_mac);
    printf("\nNext Layer: %s", e->ethertype);

    printf("\nSource IP: %s", i->src_ip);
    printf("\nDst IP: %s", i->dst_ip);

    printf("\n");
}
