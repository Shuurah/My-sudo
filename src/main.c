/*
** EPITECH PROJECT, 2025
** process file
** File description:
** proceed
*/

#include "main.h"
//#include "../include/main.h"

bool is_valid_user(char *user)
{
    FILE *fp;
    char line[1024];
    char *token;

    if (user == NULL)
        return false;
    fp = fopen("/etc/passwd", "r");
    if (fp == NULL)
        return false;
    while (fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line, ":");
        if (token != NULL && strcmp(token, user) == 0) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

bool is_valid_group(char *group)
{
    FILE *fp;
    char line[1024];
    char *token;

    if (group == NULL)
        return false;
    fp = fopen("/etc/group", "r");
    if (fp == NULL)
        return false;
    while (fgets(line, sizeof(line), fp) != NULL) {
        token = strtok(line, ":");
        if (token != NULL && strcmp(token, group) == 0) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

bool execute_as_user(uid_t uid, gid_t gid, sudo_arg_t *sudo)
{
    if (setgid(gid) != 0) {
        perror("setgid failed");
        return false;
    }
    if (setuid(uid) != 0) {
        perror("setuid failed");
        return false;
    }
    execvp(sudo->command_args[0], sudo->command_args);  
    perror("execve failed");
    return false;
}

static void init_all(sudo_arg_t *sudo)
{
    sudo->current_user = get_name_from_uid(getuid());
    sudo->target_user = "root";
    sudo->target_group = "root";
}

int setup_sudo_context(int argc, char *argv[], sudo_arg_t *sudo)
{
    int cmd_index;

    init_all(sudo);
    check_help(argc, argv);
    cmd_index = find_command_index(argc, argv);
    sudo->command_args = &argv[cmd_index];
    for (int i = 1; i < cmd_index; i++){
        if (argv[i][0] == '-'){
            parsing_arguments(sudo, i, argv);
        }
    }
    return 0;
}

static int execute_sudo(sudo_arg_t *sudo)
{
    uid_t target_uid;
    gid_t target_gid;

    if (!authenticate_user(sudo, 3)){
        return 84;
    }
    target_uid = get_uid_from_user(sudo->target_user);
    target_gid = get_gid_from_group(sudo->target_group);
    if (target_uid == (uid_t)-1 || target_gid == (gid_t)-1) {
        fprintf(stderr, "Failed to get target user/group IDs\n");
        return 84;
    }
    execute_as_user(target_uid, target_gid, sudo);
    return 84;
}

int main(int argc, char *argv[])
{
    sudo_arg_t sudo = {0};
    int result;

    setup_sudo_context(argc, argv, &sudo);
    result = execute_sudo(&sudo);
    free(sudo.current_user);
    return result;
}
