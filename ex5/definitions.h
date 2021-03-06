#ifndef PROJECT_DEFINITIONS_H
#define PROJECT_DEFINITIONS_H

#include <stdlib.h>
#include <string>

/**
 * Error message definitions
 */
#define WRONG_SERVER_USAGE "Usage: whatsappServer portNum"
#define WRONG_CLIENT_USAGE "Usage: whatsappClient clientName serverAddress portNum"
#define INVALID_CMD "ERROR: Invalid input."
#define SYS_CALL_FAIL(system_call_name) std::cout << "ERROR: " << system_call_name << " " << errno << std::endl

/**
 * Server output messages
 */
#define SERVER_SHUTDOWN_MESSAGE "EXIT command is typed: server is shutting down"
#define CREATE_GRP_SUCCESS(client, group) client + ": Group \"" + group + "\" was created successfully."
#define CREATE_GRP_FAILURE(client, group) client + ": ERROR: failed to create group " + group + "."
#define SEND_SUCCESS(sender, message, name) sender + ": \"" + message + "\" was sent successfully to " + name + "."
#define SEND_FAILURE(sender, message, name) sender + ": ERROR: failed to send \"" + message + "\" to " + name + "."
#define WHO_REQUEST(client) client + ": Requests the currently connected client names."
#define EXIT_REQUEST(client) client + ": Unregisterd successfully."

/**
 * Client output messages
 */
#define CREATE_GRP_SUCCESS_CLI(group) "Group " + group + " was created successfully."
#define CREATE_GRP_FAILURE_CLI(group) "ERROR: failed to create group " + group + "."
#define SEND_SUCCESS_CLI "Sent successfully."
#define SEND_FAILURE_CLI "ERROR: failed to send."
#define CLIENT_WHO_FAIL "ERROR: failed to receive list of connected clients."
#define CLIENT_EXIT "Unregistered successfully."

/**
 * Command strings definitions
 */
const std::string CREATE_GROUP_CMD = "create_group", SEND_CMD = "send", SERVER_SHUTDOWN = "EXIT",
        WHO_CMD = "who", EXIT_CMD = "exit", CON_SUCCESS = "consucc", INVALID_USERNAME = "invuname"
        "use.";

/**
 * Constraints
 */
#define MAX_CLIENT_NAME 30
#define MAX_CLIENTS 34
#define MAX_MESSAGE_LENGTH 255

/**
 * Constants
 */
#define MESSAGE_END '\n'
#define GROUP_UNAME_DELIM ','


#endif //PROJECT_DEFINITIONS_H
