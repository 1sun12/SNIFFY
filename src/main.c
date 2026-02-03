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
#include "payl.h"

/*
==================================================
MAIN
==================================================
*/
int main(int argc, char **argv) {
    OUTPUT_D_MSG("~ MAIN EXECUTION STARTING ~");

    ssize_t brvd = 0;

    // ~ Testing: create a socket
    sock_t *s = sock_create();

    // ~ Testing: fill out hints
    s->fill_hints(s);

    // ~ Testing: open socket
    s->open(s);

    // ~ Testing: recieve a frame
    brvd = s->recv(s);

    // ~ If recieve came back with -1, it failed and a force exit must be made :'[
    if (brvd < 0) {
        exit_with_error("\n[ERROR]:main");
    }

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
    
    // ~ Testing: payload parsing into hex-dump
    size_t headers_len = 0;
    headers_len = 14 + (i->hdr->ihl * 4) + (t->hdr->doff * 4); // ~ Calculate the length in bytes (Eth Hdr) + (IP Hdr) + (TCP Hdr)
    payl_t *p = payl_create();
    p->set_buffer(p, s->buffer, brvd, headers_len);
    p->parse(p);

    printf("\nSource MAC: \t%s", e->src_mac);
    printf("\nDst MAC: \t%s", e->dst_mac);
    printf("\nNext Layer: \t%s", e->ethertype);

    printf("\nSource IP: \t%s", i->src_ip);
    printf("\nDst IP: \t%s", i->dst_ip);

    printf("\nSource Port: \t%s", t->src_port);
    printf("\nDst Port: \t%s", t->dst_port);

    printf("\nTest Dump: \t%s", p->hex_line);

    printf("\n");
}