#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 1024

static char full_path[MAX_PATH_LENGTH];

// Function to check if a file is executable
int is_executable(const char *path) {
    return access(path, X_OK) == 0;  // Return 0 if executable
}

// Function to get the full path of a command by searching through the PATH
char *get_full_path_from_command(const char *cmd) {
    const char *path = getenv("PATH");
    if (path == NULL) {
        return NULL;  // PATH is not set
    }

    char *path_copy = strdup(path);  // Create a copy of the PATH
    if (path_copy == NULL) {
        return NULL;  // Memory allocation failed
    }

    char *dir = strtok(path_copy, ":");  // Tokenize PATH by ":"

    // Iterate over directories in PATH
    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);  // Form full path

        // Check if the file exists and is executable
        if (is_executable(full_path)) {
            free(path_copy);  // Free the copied PATH string
            return full_path;  // Return the full path
        }

        dir = strtok(NULL, ":");  // Get next directory in PATH
    }

    free(path_copy);  // Free the copied PATH string if not found
    return NULL;  // Command not found in any of the directories
}

void handle_type_command(const char *cmd) {
    // Check for built-in commands
    if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "exit") == 0 || strcmp(cmd, "type") == 0) {
        printf("%s is a shell builtin\n", cmd);
    } else {
        // Search for the command in PATH and print the result
        char *path = get_full_path_from_command(cmd);
        if (path) {
            printf("%s is %s\n", cmd, path);  // Print full path of the command
        } else {
            printf("%s: not found\n", cmd);  // Command not found
        }
    }
}

int main() {
    while (1) {
        printf("$ ");
        fflush(stdout);

        char input[MAX_PATH_LENGTH];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle EOF or read error
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit if input is "exit"
        if (strcmp(input, "exit 0") == 0) {
            break;
        }

        char *token = strtok(input, " ");
        while (token != NULL) {
            if (strcmp(token, "exit") == 0) {
                break;
            } else if (strcmp(token, "echo") == 0) {
                token = strtok(NULL, " ");
		while(token!=NULL){
			printf("%s", token);
			token = strtok(NULL," ");
			if(token!=NULL){
				printf(" ");
			}	
		}
		printf("\n");
            } else if (strcmp(token, "type") == 0) {
                token = strtok(NULL, " ");
                if (token) {
                    handle_type_command(token);
                    break;  // Break the loop after handling the type command
                }
            } else {
                printf("%s: command not found\n", token);
            }
            token = strtok(NULL, " ");
        }
    }

    return 0;
}
