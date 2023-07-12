#include <iostream>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <cstring>


void shell_loop();

void shell_launcher(char **arguments);

std::vector<std::string> shell_parse(std::string user_input);

int main() {
    printf("Starting\n");

    shell_loop();

    return 0;
}

void shell_loop() {
    char *line;
    char **args;

    const int BUF_SIZE = 20;

    char input[BUF_SIZE];

    int status;

    std::string user_input;

    do {
        printf("> ");
        std::getline(std::cin, user_input, '\n');
//        user_input = "awe bwefa zzvv\n";
        std::vector<std::string> parsed_array;
        parsed_array = shell_parse(user_input);

        for (int i = 0; i < parsed_array.size(); i++) {
            printf("%s\n", parsed_array[i].c_str());
        }

        char *char_arry[parsed_array.size()+1];

        for (int i = 0; i < parsed_array.size(); i++) {
            int token_size = ((std::string) parsed_array[i].c_str()).size();
            char_arry[i] = new char[token_size];
            strcpy(char_arry[i], (char *) parsed_array[i].c_str());
        }
        char_arry[parsed_array.size()] = NULL;

        char *ptr = (char *) &parsed_array[0];
        char **pptr = (char **) &char_arry;

        shell_launcher(pptr);

        status = strcmp("quit", input);

    } while (status);
}

std::vector<std::string> shell_parse(std::string user_input) {
    int BUF_SIZE = 64;
    const char delim = ' ';
    char **tokens = (char **) malloc(BUF_SIZE * sizeof(char *));

    *tokens = (char *) user_input.data();

    std::vector<std::string> token_vector;

    char *token;
    token = strtok(*tokens, &delim);
    while (token != NULL) {
//        printf("%s\n", token);
        token_vector.emplace_back(token);
//        printf("%s\n", token_vector[0].c_str());
        token = strtok(NULL, &delim);

    }
    return token_vector;
}

void shell_launcher(char **arguments) {
    pid_t pid, wait_pid;
    int status;

    pid = fork();
    if (pid == 0) {
        printf("I'm a child process\n");

//        int execv_ret = execvp(arguments[0], arguments);
//        if (execv_ret == -1) {
//            perror("Error: ");
//        }

        std::cout << arguments << std::endl;
        std::cout << arguments[0] << std::endl;
        std::cout << arguments[1] << std::endl;
        std::cout << sizeof(arguments) << std::endl;
        std::cout << sizeof(*arguments) << std::endl;

    } else if (pid > 0) {
        printf("I'm a parent process\n");
        do {
            wait_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    } else if (pid < 0) {
        perror("Error: ");
    }
}

