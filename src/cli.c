
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

    new->opt_tcp = 1;
    new->opt_udp = 0;
    new->opt_arp = 0;
    new->opt_output_file = 0;
    new->opt_output_terminal = 1;

    new->display_menu = cli_display_menu;
    new->display_options = cli_display_options;
    new->handle_options = cli_handle_options;
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
    printf("[o] Options\n");
    printf("[e] Exit\n");
    printf("\n> ");
    fflush(stdout);
}

void cli_display_options(cli_t *self) {
    does_exist(self);

    printf("\n=== Options ===\n");
    printf("[0] TCP: %s\n", self->opt_tcp ? "true" : "false");
    printf("[1] UDP: %s\n", self->opt_udp ? "true" : "false");
    printf("[2] ARP: %s\n", self->opt_arp ? "true" : "false");
    printf("[3] Output to file: %s\n", self->opt_output_file ? "true" : "false");
    printf("[4] Output to terminal: %s\n", self->opt_output_terminal ? "true" : "false");
    printf("\nType number + 't' or 'f' (e.g., \"1t\" to enable UDP)\n");
    printf("Type 'b' to go back\n");
    printf("\nWARNING: Only TCP is currently supported. Changing settings may cause errors.\n");
    printf("\n> ");
    fflush(stdout);
}

void cli_handle_options(cli_t *self) {
    does_exist(self);

    char input[16];
    int in_options = 1;

    while (in_options == 1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }

        if (input[0] == 'b' || input[0] == 'B') {
            in_options = 0;
            break;
        }

        if (input[1] == 't' || input[1] == 'T' || input[1] == 'f' || input[1] == 'F') {
            int value = (input[1] == 't' || input[1] == 'T') ? 1 : 0;

            if (input[0] == '0') {
                self->opt_tcp = value;
            } else if (input[0] == '1') {
                self->opt_udp = value;
            } else if (input[0] == '2') {
                self->opt_arp = value;
            } else if (input[0] == '3') {
                self->opt_output_file = value;
            } else if (input[0] == '4') {
                self->opt_output_terminal = value;
            }
        }

        self->display_options(self);
    }
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