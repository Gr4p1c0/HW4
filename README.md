# Compilation Instructions

```bash
gcc -o <executable name> <filename> # this will compile the filename and return an executable with
the executable name

gcc -o hw4 HW4.c # this will compile lab11.c and output an executable called lab11
```

# Run-Executable Instructions

```bash
./hw4 1

./hw4 2

./hw4 4

# My Files
## HW4.c

### void submit(char *line)
Void function used to create a queue/array of jobs to be processed.

### void showjobs()
Void function used to show the current status of queue/array of jobs.

### int main()
Main fucntion used to allow the user to create jobs, allowing only the number passed as the initial
argument to run concurrently.

# Output screenshots
N/A

# References
N/A