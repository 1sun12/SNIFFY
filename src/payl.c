

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
    does_exist(self);
    OUTPUT_D_MSG("payl_set_buffer : Attempting to set buffer info for the payload parser...");

    // ~ Point buffer to the location of the recieved packet
    self->buffer = buff;

    // ~ Calculate size of the payload portion of the packet (so we know when to stop and not overflow)
    self->payl_len = total_len - (headers_len);

    // ~ Set our -1/+1 byte shifter at the beginning of the payload, were ready to go!
    self->shift = ((uint8_t *)self->buffer) + headers_len;

    OUTPUT_D_MSG("payl_set_buffer : Successfully set the buffer info for the payload parser!");
}

void payl_parse(payl_t *self) {
    does_exist(self);
    OUTPUT_D_MSG("payl_parse : Attempting to hex-dump the payload...");

    // ~ The amount of bytes processed
    size_t bytes_proc = 0;

    while (bytes_proc < self->payl_len){      
        // ~ Write at each byte in our string-hex-buffer (taking advantage of pointer arithmetic magic)
        char *write_at_addr_in_hex_line = self->hex_line;

        // ~ Construct a (16)-hex-character string
        if (self->payl_len - bytes_proc >= 16) {
            for (int i = 0; i < 16; i++) {
                sprintf(write_at_addr_in_hex_line, "%02X ", self->shift[i + bytes_proc]);
                write_at_addr_in_hex_line += 3;
                bytes_proc += 1;
            }
        } else { // ~ There are not enough bytes left to make a (16)-hex-character string
            size_t bytes_remain = self->payl_len - bytes_proc;
            for (int i = 0; i < bytes_remain; i++) {
                sprintf(write_at_addr_in_hex_line, "%02X ", self->shift[i + bytes_proc]);
                write_at_addr_in_hex_line += 3;
                bytes_proc += 1;
            }
        }

        // ~ Print the hex parsed payload :]
        printf("\n%s", self->hex_line);
    }

    OUTPUT_D_MSG("payl_parse : Successfully hex-dumped the entire payload!");
}