#include <iostream>
#include <unistd.h>

void shell_loop();

void shell_launcher(char** arguments);

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

    do {
        printf("> ");
        std::cin >> input;
        std::cout << input << std::endl;

        char first = 'a', second = 'b';

        char* args_arry[] = {&first, &second};
        char** pointer = &args_arry[0];

        shell_launcher(pointer);

        status = strcmp("quit", input);

    } while (status);
}

void shell_launcher(char** arguments) {
    pid_t pid, wait_pid;
    int status;

    pid = fork();
    if (pid == 0) {
        printf("I'm a child process\n");

        int execv_ret = execvp(arguments[0], arguments);
        if (execv_ret == -1) {
            perror("Error: ");
        }

        std::cout << arguments << std::endl;
        std::cout << *arguments[0] << std::endl;
        std::cout << *arguments[1] << std::endl;
        std::cout << sizeof(*arguments) << std::endl;

    } else if (pid > 0){
        printf("I'm a parent process\n");
        do {
            wait_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    } else if (pid < 0){
        perror("Error: ");
    }
}

