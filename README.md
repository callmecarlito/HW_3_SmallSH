# HW_3_SmallSH
This is my attempt at developing a UNIX based shell command interpreter. This is a project that I'm working on for my CS344 (Operating Systems) course. On top of working on my skills in programming in the C language, I also wanted to better my understanding of version control systems, as well as attempting to document the entire process as I work through the project. 

## Files
Along with this README file are 2 additional files:
1.  makefile
2.  input_handling.c

## Features
This shell currently will have three built in commands: exit, status, and cd.
1. exit - when called should check for child processes before exiting the shell
2. status - provides the user with the exit or termination code of the most recent child processes to end
3. cd - used to change the current working directory of the shell

All additional UNIX commands can be used. Program will handle execution by creating additional processes
with fork() and using execvp() to execute command.

## Requirements
1. Must be written in C
2. Should run similar to bash, minus the fancier features
3. Allow for redirection of stdin/stdout
4. Support foreground/background processes
5. Will have three built-in commands
   - a. cd 
        - Changes working directory of shell.
        - Can be used with a single argument, which is the path to change directory to 
          - Should support relative and absolute paths
          - Shell's working directory will begin in the directory it's executed from 
        - With no arguments, it changes to the directory specified in the HOME environment variable
   - b. status
        - Prints exit status or terminating signal of the last foreground process
          - Processes killed by signals will not have an exit status
          - If ran before any foreground process has been called, it should return 0
          - Should ignore built-in commands
   - c. exit
        - Exits Shell
        - Must kill any other processes started by the shell before terminating itself
   - Shell will not support input/output redirections with these commands
   - These commands will not set any exit status
   - Shell will not support running these commands in the background
     - `&` will be ignored and command will be ran in the foreground
6. Must support comments (lines beginning with #) and blank lines
7. The prompt for the command line should simply be `: `
   - (NOTE: make sure to flush output buffers anytime text is to be printed to the screen)
8. General syntax for the command line is, where items in the square brackets are optional: 
   - `command [arg1 arg2 ...] [< input_file] [> output_file] [&]`
   - Assume every argument will be separated with a single space
   - If input or output are to be redirected, the redirection should be followed by the file name
   - Shell is not currently supporting quotation marks, so arguments with spaces are will not be 
     possible at this point.
   - Pipe operator "|" will not be implemented
9. Support command lines with a maximum length of 2048
10. Support a maximum of 512 arguments
11. Command execution should utilize fork(), exec(), and waitpid()
    - Applies to non built-in commands
    - Input/Output redirection should be done prior to exec() being called
      - redirection handled using dup2()
12. Program must expand any instance of '$$' to the process ID of the shell itself
13. Shell should wait for completion of foreground commands(child process) before prompting for the next command. 
14. With background commands, the prompt will imediately display allowing user to enter the next set of commands for execution.
    - Parent should periodically check for the background process to complete with waitpid(NOHANG)
      - Considering storing PIDs of non-completed child processes
      - It would be a good idea to check for terminated process just prior to prompting for a new command
    - stdin should be redirected from /dev/null, if user doesn't supply a file to take standard input from
    - Output from background processes should not output to the screen
      - stdout should be redirtected to /dev/null, if user doesn't specify or supply a target file
    - Process id of background process should print to screen as soon as it begins
    - When a background process terminates, the process id and exit status should print to screen
15. Ctrl-C will trigger a SIGINT signal to be sent to parent and children processes, 
    - Make sure SIGINT does not terminate the shell
    - Should only terminate the current foreground command, if one is running
    - Will need to implement signal handlers using sigaction()
    - Parent should not terminate the foreground process
      - Foreground (child) process must terminate itself
      - When this occurs, parent shell should immediately print out the number of the signal that killed the process
      - Background processes should continue to run until completion or terminated when the shell exits
16. Ctrl-Z will trigger a SIGSTP signal  
    - Upon receipt Shell, should print an informative message
      - Should print if shell is sitting at prompt, otherwise immediately after the foreground process terminates
      - Should enter a state where `&` is ingnored and commands will be run in the foreground
    - If user sends a SIGSTP signal again
      - Should print another message
      - Return the shell to the original state allowing for background processes
    - Foreground and background processes should ignore SIGSTP

## Structure
### run_shell.c
Contains main method driving the shell.

### input_handling.h / input_handling.c
Contains the methods needed to read user input from stdin, process the input, and pass it downstream for 
execution of commands. 
##### task list
- [ ] what to do if user enters leading whitespace(s)
- [ ] test handling of inputs that exceed the maximum number of arguments


## compiling and running
Make sure to keep all the program files within the same directory. To compile from the terminal, 
navigate your way to the directory where the files can be found and type "make all" followed by
enter key. Once complete the smallsh executable file should appear in the same directory. To run the 
program, simply type "./smallsh" into the terminal followed by the enter key. There is a welcome 
included, but have disabled for the purpose of grading. For grading, you will simply see the ":" 
appear after starting the program and at the point commands can be entered.

A "make clean" option has also been added, should you like you can utilize that to remove the executable
files from the directory. 

If you have any additional questions, please feel free to contact me.

Thanks!

written by: Carl S. (sinocruc@oregonstate.edu)
