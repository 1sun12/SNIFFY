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

    // ~ Testing: Ethernet Header parsing
    eth_t *e = eth_create();
    e->set_buffer(e, s->buffer);
    e->parse(e);

    // ~ Testing: IP parsing
    ip_t *i = ip_create();
    i->set_buffer(i, s->buffer);
    i->parse_src(i);
    i->parse_dst(i);

    // ~ Testing: tcp parsing
    tcp_t *t = tcp_create();
    t->set_buffer(t, s->buffer, i->hdr->ihl * 4);
    t->parse_src(t);
    t->parse_dst(t);

    printf("\nSource MAC: \t%s", e->src_mac);
    printf("\nDst MAC: \t%s", e->dst_mac);
    printf("\nNext Layer: \t%s", e->ethertype);

    printf("\nSource IP: \t%s", i->src_ip);
    printf("\nDst IP: \t%s", i->dst_ip);

    printf("\nSource Port: \t%s", t->src_port);
    printf("\nDst Port: \t%s", t->dst_port);

    printf("\n");
}
