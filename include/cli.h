#ifndef CLI_H
#define CLI_H

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

typedef struct cli_t cli_t;
struct cli_t {
    int running;
    int exit_program;

    int opt_tcp;
    int opt_udp;
    int opt_arp;

    void (*display_menu)(cli_t *self);
    void (*display_options)(cli_t *self);
    void (*handle_options)(cli_t *self);
    int (*check_for_input)(cli_t *self, int sockfd);
    void (*destroy)(cli_t **self_ptr);
};

cli_t *cli_create();

void cli_destroy(cli_t **self_ptr);

void cli_display_menu(cli_t *self);

void cli_display_options(cli_t *self);

void cli_handle_options(cli_t *self);

int cli_check_for_input(cli_t *self, int sockfd);

#endif
