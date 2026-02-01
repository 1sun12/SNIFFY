

#include "parse_ether.h"

parse_ether *parse_ether_create() {
    OUTPUT_D_MSG("parse_ether_create : Creating a new ethernet parser...");

    // ~ Create a new ethernet parser
    parse_ether *new = NULL;

    // ~ Allocate however many bytes are needed and zero + error check
    new = (parse_ether *)calloc(1, sizeof(parse_ether));
    if (new == NULL) {
        perror("\n[ERROR]:parse_ether_create");
    }

    // ~ Initialize ethernet header with default value, no need to malloc because this will point to existing memory already (our buffer)
    new->eth = NULL;

    // ~ Return the newly created parser
    OUTPUT_D_MSG("parse_ether_create : Successfully created ethernet parser!");
    return new;
}

void parse_ether_destroy(parse_ether **self_ptr) {
    // not doing this yet
}

void set_buffer(parse_ether *self, void *buffer) {
    OUTPUT_D_MSG("set_buffer : Casting buffer to ethernet header structure...");

    // ~ Cast buffer to ethernet header structure
    self->eth = (struct ethhdr *)buffer;

    OUTPUT_D_MSG("set_buffer : Successfully casted buffer space to an ethernet header structure!");
}

void parse(parse_ether *self) {
    OUTPUT_D_MSG("parse : Parsing Ethernet Header and extracting MAC addresses + next layer...");

    // ~ Convert source MAC address to a string, from the ethernet header
    sprintf(self->src_mac, "%02X:%02X:%02X:%02X:%02X:%02X",
        self->eth->h_source[0],
        self->eth->h_source[1],
        self->eth->h_source[2],
        self->eth->h_source[3],
        self->eth->h_source[4],
        self->eth->h_source[5]);

    // ~ Convert destination MAC address to a string, from the ethernet header
    sprintf(self->dst_mac, "%02X:%02X:%02X:%02X:%02X:%02X",
        self->eth->h_dest[0],
        self->eth->h_dest[1],
        self->eth->h_dest[2],
        self->eth->h_dest[3],
        self->eth->h_dest[4],
        self->eth->h_dest[5]);

    uint16_t ethertype_net = ntohs(self->eth->h_proto);

    sprintf(self->ethertype, "0x%04X", ethertype_net);

    OUTPUT_D_MSG("parse : Successfully parsed the Ethernet Header!");
}