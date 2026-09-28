/*
** EPITECH PROJECT, 2025
** process file
** File description:
** proceed
*/

#include "main.h"

void check_help(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-h") == 0){
        print_help();
        exit(0);
    }
    return;
}

void print_help(void)
{
    printf("usage: ./my_sudo -h\n");
    printf("usage: ./my_sudo [-ug] [command [args ...]]\n");
}

int find_command_index(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return i;
        }
        if ((argv[i][1] == 'u' || argv[i][1] == 'g') && i + 1 < argc)
            i++;
    }
    if (argc == 1){
        print_help();
        exit(84);
    }
    fprintf(stderr, "Error:invalid parameter\n");
    exit(84);
    return 0;
}

int parsing_arguments(sudo_arg_t *sudo, int i, char *argv[])
{
    if (argv[i][1] == 'u'){
        sudo->arg_u = true;
        if (is_valid_user(argv[i + 1])){
            sudo->target_user = argv[i + 1];
            return 0;
        }
    }
    if (argv[i][1] == 'g'){
        sudo->arg_g = true;
        if (is_valid_group(argv[i + 1])){
            sudo->target_group = argv[i + 1];
            return 0;
        }
    }
    fprintf(stderr, "Unknown option: %s\n", argv[i]);
    exit(84);
}
