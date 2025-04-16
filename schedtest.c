#include "types.h"
#include "stat.h"
#include "user.h"

void printUsage();

int main(int argc, char * argv[]) {
    // Check arg counts
    if (argc < 3 || argc > 9) {
        printUsage();
        exit();
    }
    
    // Check loop arg
    int loops = -1;

    loops = atoi(argv[1]);
    if (loops <= 0) {
        printUsage();
        exit();
    }

    // Check tickets args
    int tickets[7] = {0};
    int i;
    for (i = 0; i < (argc-2); i++) {
        if ((tickets[i] = atoi(argv[i+2])) < 10) {
            printUsage();
            exit();
        }
    }

    // Create child processes
    int nc;
    int pids[7] = {0};
    for (nc=0; nc < i; nc++) {
        if ((pids[nc] = fork()) == 0) {
            settickets(tickets[nc]);
            for (;;) { }
        }
    }


    // Call ps loop times
    for (nc = 0; nc < loops; nc++) {
        ps();
        sleep(3);
    }

    // Kill the children
    for (nc = 0; nc < i; nc++) {
        kill(pids[nc]);
    }

    // Reap the fallen children
    while (wait() > 0) { }

    exit();
}

void printUsage() {
    printf(1, "usage: schedtest loops tickets1 [ tickets2 ... ticketsN ]\n\
    loops must be greater than 0\n\
    tickets must be greater than or equal to 10\n\
    up to 7 tickets can be provided\n");
}

