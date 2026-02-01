

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