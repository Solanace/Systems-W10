#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static void sighandler(int signo) {
    if (signo == SIGINT) {
        char s[] = "Exiting due to SIGINT\n";
        int fd = open("message.txt", O_CREAT | O_WRONLY, 0644);
        write(fd, s, sizeof(s));
        close(fd);
        exit(1);
    }
    
    if (signo == SIGUSR1) {
        printf("Parent PID: %d\n", getppid());
    }
}

int main() {
    umask(0);
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while (1) {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
    
    return 0;
}
