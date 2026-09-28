/*
** EPITECH PROJECT, 2025
** process file
** File description:
** proceed
*/

#include "main.h"

static char *extract_username_from_line(char *line, uid_t uid)
{
    char *token;
    char *username;
    uid_t current_uid;

    username = strtok(line, ":");
    if (username == NULL)
        return NULL;
    strtok(NULL, ":");
    token = strtok(NULL, ":");
    if (token == NULL)
        return NULL;
    current_uid = atoi(token);
    if (current_uid == uid)
        return strdup(username);
    return NULL;
}

char *get_name_from_uid(uid_t uid)
{
    FILE *fp;
    char line[1024];
    char *result;

    fp = fopen("/etc/passwd", "r");
    if (fp == NULL)
        return NULL;
    while (fgets(line, sizeof(line), fp) != NULL) {
        result = extract_username_from_line(line, uid);
        if (result != NULL) {
            fclose(fp);
            return result;
        }
    }
    fclose(fp);
    return NULL;
}

static char *extract_groupname_from_line(char *line, gid_t gid)
{
    char *token;
    char *groupname;
    gid_t current_gid;

    groupname = strtok(line, ":");
    if (groupname == NULL)
        return NULL;
    strtok(NULL, ":");
    token = strtok(NULL, ":");
    if (token == NULL)
        return NULL;
    current_gid = atoi(token);
    if (current_gid == gid)
        return strdup(groupname);
    return NULL;
}

char *get_name_from_gid(gid_t gid)
{
    FILE *fp;
    char line[1024];
    char *result;

    fp = fopen("/etc/group", "r");
    if (fp == NULL)
        return NULL;
    while (fgets(line, sizeof(line), fp) != NULL) {
        result = extract_groupname_from_line(line, gid);
        if (result != NULL) {
            fclose(fp);
            return result;
        }
    }
    fclose(fp);
    return NULL;
}

static uid_t extract_uid_from_line(char *line, char *username)
{
    char *token;
    uid_t uid;

    token = strtok(line, ":");
    if (token == NULL || strcmp(token, username) != 0)
        return (uid_t)-1;
    strtok(NULL, ":");
    token = strtok(NULL, ":");
    if (token == NULL)
        return (uid_t)-1;
    uid = atoi(token);
    return uid;
}

uid_t get_uid_from_user(char *username)
{
    FILE *fp;
    char line[1024];
    uid_t uid;

    if (username == NULL)
        return (uid_t)-1;
    fp = fopen("/etc/passwd", "r");
    if (fp == NULL)
        return (uid_t)-1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        uid = extract_uid_from_line(line, username);
        if (uid != (uid_t)-1) {
            fclose(fp);
            return uid;
        }
    }
    fclose(fp);
    return (uid_t)-1;
}

static gid_t extract_gid_from_line(char *line, char *groupname)
{
    char *token;
    gid_t gid;

    token = strtok(line, ":");
    if (token == NULL || strcmp(token, groupname) != 0)
        return (gid_t)-1;
    strtok(NULL, ":");
    token = strtok(NULL, ":");
    if (token == NULL)
        return (gid_t)-1;
    gid = atoi(token);
    return gid;
}

gid_t get_gid_from_group(char *groupname)
{
    FILE *fp;
    char line[1024];
    gid_t gid;

    if (groupname == NULL)
        return (gid_t)-1;
    fp = fopen("/etc/group", "r");
    if (fp == NULL)
        return (gid_t)-1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        gid = extract_gid_from_line(line, groupname);
        if (gid != (gid_t)-1) {
            fclose(fp);
            return gid;
        }
    }
    fclose(fp);
    return (gid_t)-1;
}
