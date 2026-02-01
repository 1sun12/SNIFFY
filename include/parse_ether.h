#ifndef PARSE_ETHER_H
#define PARSE_ETHER_H

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

#include <netinet/if_ether.h>

typedef struct {
    struct ethhdr *eth;
    // source mac?
    // destination mac?
    // next protocol? 
} parse_ether;

parse_ether *parse_ether_create();

void parse_ether_destroy(parse_ether **self_ptr);

void set_buffer(parse_ether *self, void *buffer);

#endif