#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80

void initialize_args(char* args[]) {
    for (int i = 0; i < MAX_LINE/2 + 1; i++) {
        args[i] = NULL;
    }
}

void initialize_command(char* command) {
    command = strcpy(command, "");
}

int readline_to_command(char* command) {
    char input[MAX_LINE + 1];
    fgets(input, MAX_LINE + 1, stdin);

    // check if input is empty or contains only spces
    size_t input_len = strspn(input, " \t\n\v\f\r");
    if (input_len == strlen(input)) { // null input or only spaces
        printf("Please enter your command or 'exit' to terminate\n");
        return 0;
    }

    // remove trailing newline character
    if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    if (strcmp(input, "!!") == 0) {
        // check if there is previous command
        if (strlen(command) == 0) {
            printf("No commands in history.\n");;
            return 0;
        }
        printf("%s\n", command);
        return 1; 
    }

    strcpy(command, input);

    return 1;
}

int parse_command(char* args[], char* command) {
    // tokenize the command line into args and return the number of tokens
    // command would be tokenized after the strtok
    char command_cpy[MAX_LINE + 1];
    char* deliminator = " ";
    int idx = 0;
    
    strcpy(command_cpy, command);

    char* token = NULL;
    token = strtok(command_cpy, deliminator);
    while (token != NULL) {
        args[idx] = malloc(strlen(token) + 1);
        strcpy(args[idx], token);
        idx++;
        token = strtok(NULL, deliminator); // tells strtok() to continue tokenizing the string from where it left off in the previous call
    }

    return idx + 1; // number of tokens
}

void refresh_args(char* args[]) {
    while (*args) {
        free(*args);
        *args++ = NULL;
    }
}

void printArgs(char* args[]) {
    for (int i = 0; args[i] != NULL; i++) {
        printf("index: %d, token: %s\n", i, args[i]);
    }
}

int run_command(char* args[]) {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 0;
    }
    else if (pid == 0) {
        // terminate the child process if user enter invalid command
        if (execvp(args[0], args) == -1) { // 為什麼child_process讀得到？
            printf("%s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else {
        wait(NULL);
    }
    return 1;
}

int main(void) {
    char command[MAX_LINE + 1]; 
    char* args[MAX_LINE/2 + 1]; // there at most 40 tokens
    int args_count = 0;
    initialize_args(args);
    initialize_command(command);

    while (1) {
        printf("osh>");
        fflush(stdout);
        
        // read user input line into command and parse it into arguments
        // readline_to_command(command);
        if (!readline_to_command(command)) {
            continue;
        }
        refresh_args(args);
        args_count = parse_command(args, command);
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        run_command(args);

    }
    
    refresh_args(args);

    return 0;
}