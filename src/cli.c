
#include "cli.h"

cli_t *cli_create() {
    OUTPUT_D_MSG("cli_create : Attempting to create a CLI object...");

    cli_t *new = NULL;

    if ((new = (cli_t *)calloc(1, sizeof(cli_t))) == NULL) {
        perror("\n[ERROR]:cli_create");
        return NULL;
    }

    new->running = 0;
    new->exit_program = 0;

    new->display_menu = cli_display_menu;
    new->check_for_input = cli_check_for_input;
    new->destroy = cli_destroy;

    OUTPUT_D_MSG("cli_create : Successfully created a CLI object!");
    return new;
}

void cli_destroy(cli_t **self_ptr) {
    cli_t *self = *self_ptr;

    OUTPUT_D_MSG("cli_destroy : CLI object being destroyed...");

    free(self);
    *self_ptr = NULL;

    OUTPUT_D_MSG("cli_destroy : CLI object destroyed successfully!");
}

void cli_display_menu(cli_t *self) {
    does_exist(self);

    printf("\n=== Packet Sniffer ===\n");
    printf("[s] Start capture\n");
    printf("[e] Exit\n");
    printf("\n> ");
    fflush(stdout);
}

int cli_check_for_input(cli_t *self, int sockfd) {
    does_exist(self);

    fd_set read_fds;
    struct timeval tv;

    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);
    FD_SET(0, &read_fds);

    tv.tv_sec = 0;
    tv.tv_usec = 100000;

    int max_fd = sockfd > 0 ? sockfd : 0;

    int result = select(max_fd + 1, &read_fds, NULL, NULL, &tv);

    if (result < 0) {
        perror("\n[ERROR]:cli_check_for_input");
        return -1;
    }

    if (FD_ISSET(0, &read_fds)) {
        char input[16];
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (input[0] == 's' || input[0] == 'S') {
                self->running = 0;
                return 0;
            }
        }
    }

    if (FD_ISSET(sockfd, &read_fds)) {
        return 1;
    }

    return -1;
}
