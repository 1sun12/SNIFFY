
#include "parse_ip.h"

parse_ip *parse_ip_create() {
    OUTPUT_D_MSG("parse_ip_create : Attempting to create an IP parser object...");

    // ~ Create a new IP Header parser
    parse_ip *new = NULL;
    
    // ~ Allocate memory
    if ((new = (parse_ip *)calloc(1, sizeof(parse_ip))) == NULL) {
        perror("\n[ERROR]:parse_ip_create");
        return NULL;
    }

    // ~ Initialize IP Header with default value, no need to malloc because it will point at existing memory
    new->iph = NULL;

    // ~ Return newly created object
    OUTPUT_D_MSG("parse_ip_create : Successfully created an IP parser object!");
    return new;
}

void parse_source_ip(parse_ip *self) {
// code
}