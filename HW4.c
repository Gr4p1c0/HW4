/* 
Name: Keith B. Jones II
BlazerId: k91jones
Project #: HW4
To compile: "gcc -o hw4 HW4.c " 
To run: "./hw4 1"
        "./hw4 2"
        "./hw4 4"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

#define MAX_JOBS 100
#define MAX_LINE 1024

//Structure used to hold a jobs information.
struct Job {
    pid_t pid;
    char *name;
    char *args[MAX_LINE];
    char outfile[MAX_LINE];
    char errfile[MAX_LINE];
    int status;
};

//Initializations
struct Job jobs[MAX_JOBS];
int n_jobs = 0;
int max_jobs = 0;

//Void function used to create a queue of jobs to be processed.
//Returns: N/A
void submit(char *line) {
    if (n_jobs == MAX_JOBS) {
        printf("Error: Too many jobs.\n");
        return;
    }

    int n = strlen(line);

    if (line[n - 1] == '\n') {
        line[n - 1] = '\0';
    }

    char *name = strtok(line, " ");
    jobs[n_jobs].name = strdup(name);
    jobs[n_jobs].args[0] = strdup(name);

    for (int i = 1; i < MAX_LINE; i++) {
        char *arg = strtok(NULL, " ");

        if (arg == NULL || arg[0] == '\n') {
            jobs[n_jobs].args[i] = NULL;
            break;
        } else {
            jobs[n_jobs].args[i] = strdup(arg);
        }
    }

    snprintf(jobs[n_jobs].outfile, MAX_LINE, "%d.out", n_jobs);
    snprintf(jobs[n_jobs].errfile, MAX_LINE, "%d.err", n_jobs);
    pid_t pid = fork();

    if (pid == 0) {
        freopen(jobs[n_jobs].outfile, "w", stdout);
        freopen(jobs[n_jobs].errfile, "w", stderr);
        execvp(name, jobs[n_jobs].args);
        exit(1);
    } else if (pid > 0) {
        jobs[n_jobs].pid = pid;
        jobs[n_jobs].status = 1;
        printf("Job %d started.\n", n_jobs);
        n_jobs++;
    } else {
        printf("Error: Failed to create a new process.\n");
    }
}

//Void function used to show the current status of queue/array of jobs.
//Returns: N/A
void showjobs() {
    for (int i = 0; i < n_jobs; i++) {
        int status = jobs[i].status;

        if (status == 0) {
            printf("Job %d (waiting): %s\n", i, jobs[i].name);
        } else if (status == 1) {
            printf("Job %d (running): %s\n", i, jobs[i].name);
        }
    }
}

//Main fucntion used to allow the user to create jobs, allowing only the number passed
// as the initial argument to run concurrently.
// Returns: N/A 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s P\n", argv[0]);
        exit(1);
    }

    max_jobs = atoi(argv[1]);
    char line[MAX_LINE];

    while (true) {
        printf("Enter command> ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            exit(0);
        }

        if (line[0] == '#') {
            continue;
        }

        if (strncmp(line, "submit ", 7) == 0) {
            submit(line + 7);
        } else if (strcmp(line, "showjobs\n") == 0) {
            showjobs();
        } else {
            printf("Unknown command: %s", line);
        }
    }
}