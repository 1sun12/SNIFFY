#ifndef PAYL_H
#define PAYL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct payl_t payl_t;
struct payl_t {
    uint8_t shift;  // ~ Payload shifter (move -1 or +1 bytes across the payload)
    int plen;       // ~ Length of the payload in bytes
};


#endif