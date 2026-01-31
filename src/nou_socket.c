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

void nou_socket_destroy(nou_socket *self) {
    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_destroy : Nou socket being destroyed...\n");}
    
    // ~ Close the linux file descriptor for the socket
    if (close(self->sockfd) < 0) {
        perror("\n[ERROR]:nou_socket_destroy");
    }

    // ~ Deallocate this entire memory block
    free(self);

    if (OUTPUT_DEBUG) {printf("\n[INFO]:nou_socket_destroy : Nou socket destroyed successfully!\n");}
}

/*
 * ==========================================================================
 * METHODS - Functions that operate on the object
 * ==========================================================================
 *
 */

void fill_out_hints(nou_socket *self) {

}