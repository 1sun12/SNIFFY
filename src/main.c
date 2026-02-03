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
#include "cli.h"
#include "output.h"

/*
==================================================
MAIN
==================================================
*/
int main(int argc, char **argv) {
    OUTPUT_D_MSG("~ MAIN EXECUTION STARTING ~");

    ssize_t brvd = 0;
    char input[16];

    // ~ Testing: create a CLI
    cli_t *c = cli_create();

    // ~ Testing: create an output handler
    output_t *o = output_create();

    // ~ Testing: create a socket
    sock_t *s = sock_create();

    // ~ Testing: fill out hints
    s->fill_hints(s);

    // ~ Testing: open socket
    s->open(s);

    while (c->exit_program == 0) {
        c->display_menu(c);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }

        if (input[0] == 's' || input[0] == 'S') {
            c->running = 1;
            printf("\nCapturing... (type 's' + Enter to stop)\n");

            o->to_file = c->opt_output_file;
            o->to_terminal = c->opt_output_terminal;

            if (o->to_file == 1) {
                o->open_file(o);
            }

            while (c->running == 1) {
                int status = c->check_for_input(c, s->sockfd);

                if (status == 0) {
                    break;
                }

                if (status == 1) {
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

                    // ~ Skip non-IPv4 packets (ethertype must be 0x0800)
                    if (ntohs(e->hdr->h_proto) != 0x0800) {
                        e->destroy(&e);
                        continue;
                    }

                    // ~ Testing: IP parsing
                    ip_t *i = ip_create();
                    i->set_buffer(i, s->buffer);
                    i->parse_src(i);
                    i->parse_dst(i);

                    // ~ Skip non-TCP packets (protocol must be 6)
                    if (i->hdr->protocol != 6) {
                        e->destroy(&e);
                        i->destroy(&i);
                        continue;
                    }

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

                    o->writef(o, "\nSource MAC: \t%s", e->src_mac);
                    o->writef(o, "\nDst MAC: \t%s", e->dst_mac);
                    o->writef(o, "\nNext Layer: \t%s", e->ethertype);

                    o->writef(o, "\nSource IP: \t%s", i->src_ip);
                    o->writef(o, "\nDst IP: \t%s", i->dst_ip);

                    o->writef(o, "\nSource Port: \t%s", t->src_port);
                    o->writef(o, "\nDst Port: \t%s", t->dst_port);

                    o->writef(o, "\n~~ Test Dump ~~\n");
                    p->parse(p, o);

                    o->writef(o, "\n");

                    e->destroy(&e);
                    i->destroy(&i);
                    t->destroy(&t);
                }
            }

            if (o->to_file == 1) {
                o->close_file(o);
            }
        } else if (input[0] == 'o' || input[0] == 'O') {
            c->display_options(c);
            c->handle_options(c);
        } else if (input[0] == 'e' || input[0] == 'E') {
            c->exit_program = 1;
        }
    }

    s->destroy(&s);
    c->destroy(&c);
    o->destroy(&o);

    printf("\nGoodbye!\n");
    return 0;
}
