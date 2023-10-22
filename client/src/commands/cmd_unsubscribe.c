/*
** EPITECH PROJECT, 2024
** B_NWP_400_LIL_4_1_myteams_achille_bourgault
** File description:
** Created by Frederic LAWECKI--WALKOWIAK
*/

#include "../../include/myteams_client.h"
#include <string.h>
#include <stdlib.h>

int unsubscribe_error_handling(client_t *client, char **command)
{
    if (strcmp(command[0], "/unsubscribe") != 0)
        return ERROR;
    if (command[1] == NULL)
        return SUCCESS;
    if (client->connected == 0) {
        client_error_unauthorized();
        return SUCCESS;
    }
    return 0;
}

char **create_unsubscribe_arglist(char *team_uid, char *user_uid)
{
    char **arg_list = malloc(sizeof(*arg_list) * 2);

    clean_str(team_uid, '"');
    arg_list[0] = strdup(team_uid);
    arg_list[1] = strdup(user_uid);
    arg_list[2] = NULL;
    return arg_list;
}

void handle_unsubscribe_reply(client_t *client, char **reply, char *uid)
{
    if (strcmp(reply[0], "510") == 0) {
        client_print_unsubscribed(client->user_uid, uid);
    } else if (strcmp(reply[0], "511") == 0) {
        client_error_unknown_team(uid);
    }
}

int cmd_unsubscribe(client_t *client, char **command)
{
    int error_handling = unsubscribe_error_handling(client, command);
    char **arglist;
    char **reply;

    if (error_handling != 0)
        return error_handling;
    arglist = create_unsubscribe_arglist(command[1], client->user_uid);
    send_request(client, "500", arglist);
    reply = get_request(client);
    for (int i = 0; arglist[i] != NULL; i++)
        free(arglist[i]);
    for (int i = 0; reply[i] != NULL; i++)
        free(reply[i]);
    free(arglist);
    free(reply);
    return SUCCESS;
}