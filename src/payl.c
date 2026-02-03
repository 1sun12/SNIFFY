

#include "debug.h"
#include "payl.h"

payl_t *payl_create() {
    OUTPUT_D_MSG("payl_create : Attempting to create a payload parser...");

    // ~ Create new payload parser object
    payl_t *new = NULL;

    // ~ Allocate memory + error check
    new = (payl_t *)calloc(1, sizeof(payl_t));
    if (new == NULL) {
        perror("\n[ERROR]:payl_create");
        return NULL;
    }

    // ~ Default fields
    new->shift = NULL; // ~ Does not need mallocation, will be pointing at existing memory
    
    // ~ Wire up those beautiful function pointers
    new->parse = payl_parse;
    new->set_buffer = payl_set_buffer;

    // ~ Return newly created object
    OUTPUT_D_MSG("payl_create : New payload parser successfully created!");
    return new;
}

void payl_set_buffer(payl_t *self, void *buff, size_t total_len, size_t headers_len){
    // ~ Point buffer to the location of the recieved packet
    self->buffer = buff;

    // ~ Calculate size of the payload portion of the packet (so we know when to stop and not overflow)
    self->payl_len = total_len - (headers_len);

    // ~ Set our -1/+1 byte shifter at the beginning of the payload, were ready to go!
    self->shift = ((uint8_t *)self->buffer) + headers_len;
}

void payl_parse(payl_t *self) {
    OUTPUT_D_MSG("payl_parse : Attempting to hex-dump the payload...");

    // ~ Construct a (16)-hex-character line
    sprintf(self->hex_line, "%02X", self->shift[0]);
}