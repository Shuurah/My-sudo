/*
** EPITECH PROJECT, 2025
** game.h
** File description:
** header for game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include <stdbool.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <crypt.h>

typedef struct sudo_arg_s{
    bool arg_h;
    bool arg_u;
    bool arg_g;
    uid_t *uid;
    gid_t *gid;
    char *target_user;
    char *current_user;
    char *target_group;
    char **command_args;
    int command_count;
} sudo_arg_t;

bool authenticate_user(sudo_arg_t *sudo, int max_attempts);
int find_command_index(int argc, char *argv[]);
int parsing_arguments(sudo_arg_t *sudo, int i, char *argv[]);
bool is_valid_user(char *user);
bool is_valid_group(char *group);
void print_help(void);
void check_help(int argc, char *argv[]);
char *get_name_from_uid(uid_t uid);
char *get_name_from_gid(gid_t gid);
uid_t get_uid_from_user(char *username);
gid_t get_gid_from_group(char *groupname);
#endif
