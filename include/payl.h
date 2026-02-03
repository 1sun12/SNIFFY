#ifndef PAYL_H
#define PAYL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HEX_LINE_SIZE 48   // ~ One line of hex is equivalent to 0x10, then 0x20... and so on

typedef struct payl_t payl_t;
struct payl_t {
    uint8_t *shift;  // ~ Payload shifter (move -1 or +1 bytes across the payload)
    void *buffer;
    size_t payl_len;
    char hex_line[HEX_LINE_SIZE];

    // ~ Function pointers (I LOVE ABSTRACTION!!!! :DDDD)
    void (*parse)(payl_t *self);
    void (*set_buffer)(payl_t *self, void *buff, size_t total_len, size_t headers_len);
};

payl_t *payl_create();

// ~ payl_destroy();

void payl_set_buffer(payl_t *self, void *buff, size_t total_len, size_t headers_len);

void payl_parse(payl_t *self);


#endif