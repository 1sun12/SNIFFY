#ifndef PARSE_ETHER_H
#define PARSE_ETHER_H

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/if_ether.h>

typedef struct {
    struct ethhdr *eth;
    char src_mac[18];
    char dst_mac[18];
    char ethertype[7];
} parse_ether;

parse_ether *parse_ether_create();

void parse_ether_destroy(parse_ether **self_ptr);

void set_buffer(parse_ether *self, void *buffer);

void parse(parse_ether *self);


#endif