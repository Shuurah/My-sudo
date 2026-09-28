/*
** EPITECH PROJECT, 2025
** auth file
** File description:
** get auth
*/

#include "../include/main.h"
#include <crypt.h>

static char *read_password(char *username)
{
    char *password = malloc(256);
    int i = 0;
    int character_int;

    if (password == NULL)
        return NULL;
    printf("[my_sudo] password for %s: ", username);
    character_int = getchar();
    while (character_int != '\n' && character_int != EOF && i < 255) {
        password[i] = character_int;
        i++;
        character_int = getchar();
    }
    password[i] = '\0';
    if (character_int == EOF) {
        memset(password, 0, 256);
        free(password);
        return NULL;
    }
    return password;
}

static char *extract_pwd_from_line(char *line, char *username, char *result)
{
    char *token;
    char *encrypted_pwd;

    token = strtok(line, ":");
    if (token == NULL || strcmp(token, username) != 0)
        return NULL;
    encrypted_pwd = strtok(NULL, ":");
    if (encrypted_pwd == NULL)
        return NULL;
    strncpy(result, encrypted_pwd, 255);
    result[255] = '\0';
    return result;
}

static char *get_shadow_password(char *username)
{
    FILE *fp;
    char line[1024];
    char result[256];

    fp = fopen("/etc/shadow", "r");
    if (fp == NULL)
        return NULL;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (extract_pwd_from_line(line, username, result) != NULL) {
            fclose(fp);
            return strdup(result);
        }
    }
    fclose(fp);
    return NULL;
}

static void cleanup_auth(char *password, char *shadow_pwd)
{
    if (password != NULL) {
        memset(password, 0, strlen(password));
        free(password);
    }
    if (shadow_pwd != NULL)
        free(shadow_pwd);
}

bool verify_password(char *password, char *shadow_pwd)
{
    char *encrypted;

    encrypted = crypt(password, shadow_pwd);
    if (encrypted == NULL)
        return false;
    return (strcmp(encrypted, shadow_pwd) == 0);
}

bool attempt_authentication(char *username, int attempts)
{
    char *shadow_pwd;
    char *password;
    bool success;

    password = read_password(username);
    if (password == NULL)
        return false;
    shadow_pwd = get_shadow_password(username);
    if (shadow_pwd == NULL) {
        fprintf(stderr, "Sorry, try again.\n");
        cleanup_auth(password, shadow_pwd);
        return false;
    }
    success = verify_password(password, shadow_pwd);
    cleanup_auth(password, shadow_pwd);
    if (!success && attempts < 2)
        fprintf(stderr, "Sorry, try again.\n");
    if (!success && attempts == 2)
        fprintf(stderr, "my_sudo: 3 incorrect password attempts\n");
    return success;
}

bool authenticate_user(sudo_arg_t *sudo, int max_attempts)
{
    int attempts = 0;

    if (getuid() == 0)
        return true;
    while (attempts < max_attempts) {
        if (attempt_authentication(sudo->current_user, attempts))
            return true;
        attempts++;
    }
    return false;
}
