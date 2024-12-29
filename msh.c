#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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


void execute(char **cmd, char *path) {
  pid_t pid = fork();
  if(pid == 0){
    execv(path, cmd);
    printf("\n");
    perror("execv");
    exit(1);
  } else if(pid<0){
    perror("fork");
  } else {
    int status;
    waitpid(pid, &status, 0);
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
        char *args[100];
        int argc = 0;
        while(token!=NULL && argc<99){
          args[argc++] = token;
          token = strtok(NULL, " ");
        }
        args[argc] = NULL;
        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "echo") == 0) {
          for(int i=1;i<argc;i++){
            printf("%s ", args[i]);
          }
          printf("\n");
       } else if (strcmp(args[0], "type") == 0) {
            handle_type_command(args[1]);
        } else{ 
          char *path = get_full_path_from_command(args[0]);
          if(path){
            execute(args, path);
          }else printf("%s: command not found\n", args[0]);
        } 
    }

    return 0;
}
