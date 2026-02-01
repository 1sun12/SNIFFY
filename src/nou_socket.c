#include "nou_socket.h"

/*
 * ==========================================================================
 * Constructor & Destructor - Initialize and freeing "this" object
 * ==========================================================================
 */

nou_socket *nou_socket_create() {
    OUTPUT_D_MSG("nou_socket_create : Initializing a nou socket...");

    // ~ Initialize a nou socket pointer
    nou_socket *new = NULL;

    // ~ Allocate however many bytes of memory it needs and zero the entire space
    new = (nou_socket *)calloc(1, sizeof(nou_socket));

    // ~ Error check: did calloc fail?
    if (new == NULL) {
        perror("\n[ERROR]:nou_socket_create");
        return NULL;
    }

    // ~ Load default values
    new->sockfd = -1;

    // ~ Hints has already been zeroed out by calloc

    // ~ Allocate memory to the buffer and error check
    if ((new->buffer = malloc(MAX_FRAME_SIZE)) == NULL) {
        perror("\n[ERROR]:nou_socket_create");
    }

    // ~ Return the newly init struct
    OUTPUT_D_MSG("nou_socket_create : Nou socket initialized successfully!");
    return new;
}

void nou_socket_destroy(nou_socket **self_ptr) {
    nou_socket *self = *self_ptr;

    OUTPUT_D_MSG("nou_socket_destroy : Nou socket being destroyed...");
    
    // ~ Close the linux file descriptor for the socket
    if (close(self->sockfd) < 0) {
        perror("\n[ERROR]:nou_socket_destroy");
    }

    // ~ Deallocate the buffer
    free(self->buffer);
    self->buffer = NULL;

    // ~ Deallocate this entire memory block
    free(self);
    *self_ptr = NULL;

    OUTPUT_D_MSG("nou_socket_destroy : Nou socket destroyed successfully!");
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

    OUTPUT_D_MSG("fill_out_hints : Hints have been templated...");
}

void open_socket(nou_socket *self) {
    OUTPUT_D_MSG("open_socket : Opening a new socket...");

    // ~ Creates a new socket given the templated information from our address information
    if ((self->sockfd = socket(self->hints.ai_family, self->hints.ai_socktype, self->hints.ai_protocol)) < 0) {
        perror("\n[ERROR]:open_socket");
        return;
    }

    OUTPUT_D_MSG("open_socket : Successfully opened a new socket!");
}

void close_socket(nou_socket *self) {
    OUTPUT_D_MSG("close_socket : Closing an existing socket...");

    if (close(self->sockfd) < 0) {
        perror("\n[ERROR]:close_socket");
        return;
    }

    OUTPUT_D_MSG("close_socket : Successfully closed an existing socket!");
}

void recv_socket(nou_socket *self) {
    OUTPUT_D_MSG("recv_socket : Attempting to recieve message...");

    // ~ Recieve a raw ethernet frame from your Network Interface Card
    if ((recv(self->sockfd, self->buffer, MAX_FRAME_SIZE, 0)) < 0) {
        perror("\n[ERROR]:recv_socket");
        return;
    }

    OUTPUT_D_MSG("recv_socket : Successfully recieved an ethernet frame!");
}