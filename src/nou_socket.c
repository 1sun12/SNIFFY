#include "nou_socket.h"

/*
 * ==========================================================================
 * Constructor & Destructor - Initialize and freeing "this" object
 * ==========================================================================
 */

nou_socket *nou_socket_create() {
    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_create : Initializing a nou socket...\n");}

    // ~ Initialize a nou socket pointer
    nou_socket *new = NULL;

    // ~ Allocate however many bytes of memory it needs
    new = (nou_socket *)calloc(1, sizeof(nou_socket));

    // ~ Error check: did calloc fail?
    if (new == NULL) {
        perror("[ERROR]:nou_socket_create");
        return NULL;
    }

    // ~ Load default values
    new->sockfd = -1;

    // ~ Hints has already been zeroed out by calloc

    // ~ Return the newly init struct
    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_create : Nou socket initialized successfully!\n");}
    return new;
}

void nou_socket_destroy(nou_socket **self_ptr) {
    nou_socket *self = *self_ptr;

    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_destroy : Nou socket being destroyed...\n");}
    
    // ~ Close the linux file descriptor for the socket
    if (close(self->sockfd) < 0) {
        perror("\n[ERROR]:nou_socket_destroy");
    }

    // ~ Deallocate this entire memory block
    free(self);

    // ~ Set the pass-by-reference to NULL, free does not do this for you
    *self_ptr = NULL;

    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_destroy : Nou socket destroyed successfully!\n");}
}

/*
 * ==========================================================================
 * METHODS - Functions that operate on the object
 * ==========================================================================
 *
 */

void fill_out_hints(nou_socket *self) {
    does_exist(self);

    // ~ Set address family to packets
    self->hints.ai_family = AF_PACKET;

    // ~ Set socket type to raw
    self->hints.ai_socktype = SOCK_RAW;

    // ~ Set protocol to capture every packet that hits our Network Interface Card
    self->hints.ai_protocol = htons(ETH_P_ALL);

    if (OUTPUT_DEBUG) {printf("\n[INFO]:fill_out_hints : Hints have been templated...\n");}
}