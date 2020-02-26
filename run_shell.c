#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "input_handling.h"
#include "exec_cmnds.h"

#define MAX_PIDS 10

int main(){
    char* user_input = NULL; //variable will contain initial input from user
    char* cmnd_args[MAX_ARGS]; //array containing the parsed user input
    int arg_count = -5; //variable holding the number of parsed arguments
    Shell_Flags shell_flags; //struct of shell_flags used for processing commands

    pid_t child_pid = -5;
    int exit_code = -5; 
    int child_exit_status = -5;

    //pid_t pids[MAX_PIDS];
    //int bg_pid_count = 0;

    //infinitie while loop 
    while(1){
        //check pids for terminated/exitted child process
        //remove from pids array
        //print exit status of last terminated child process

        //get user input and process input into separate arguments
        arg_count = ProcessInput(user_input, cmnd_args);
        //if there's an error that occurs in ProcessInput() it will return 0
        //and will return to the top of the loop to re-attempt getting user input
        if(arg_count <= 0){continue;}
        
        int input_redir_index = 0; //holds index number for the location of "<" in the array
        int output_redir_index = 0; //holds index number for the location of ">" in the array
        char* input_redir_file = NULL; //holds value for where input redirection will occur
        char* output_redir_file = NULL; //holds value for where output redirection will occur
        
        InitializeFlags(&shell_flags); //initialize all flags to false
        SetBuiltInFlag(cmnd_args, &shell_flags); //if the 0th element refers to a built-in command, this will set the flag true
        SetBackgroundFlag(cmnd_args, arg_count, &shell_flags); //if the last element contains "&", this will set flag true
        input_redir_index = SetStdinRedirFlag(cmnd_args, arg_count, &shell_flags); //if "<" is found, flag will be set true, and the index location will be returned
        output_redir_index = SetStdoutRedirFlag(cmnd_args, arg_count, &shell_flags); //if ">" is found, flag will be set true, and the index location will be returned

        /***************************************************************************
         * Based on the flags set:
         * - Built-in commands will be executed immediately, otherwise
         * - User commands will be processed further prior to execution of non
         *   built-in commands.
         ***************************************************************************/
        if(shell_flags.built_in_flag == true){
            ExecBuiltIn(cmnd_args, exit_code); //execution of built-in commands
        }
        if(shell_flags.stdin_redirect == true){
            input_redir_file = GetRedirFile(cmnd_args, input_redir_index); //get input redirection info
        }
        if(shell_flags.stdout_redirect == true){
            output_redir_file = GetRedirFile(cmnd_args, output_redir_index); //get output redirection info
        }
        RemoveCmndArgs(cmnd_args, &arg_count, &shell_flags); //remove redirection related arguments as they have all been extracted
        /***************************************************************************
         * Based on the flags set:
         * - Built-in commands will be executed immediately, otherwise
         * - User commands will be processed further prior to execution of non
         *   built-in commands.
         ***************************************************************************/
        child_pid = fork();
        switch(child_pid){
            case -1:
                perror("Fork error: "); exit(1); break;
            case 0:
                RedirectionHandler(&shell_flags, input_redir_file, output_redir_file);
                //print pid of backgroud process before executing cmnds
                if(shell_flags.background_proc == true){ 
                    printf("background pid is: %d", getpid()); fflush(stdout);
                }
                //execute non built-in commands
                execvp(cmnd_args[0], cmnd_args);
                //if error occurs with excvp()
                perror("Execvp() error: "); exit(1); break;
            default:
                //if(shell_flags.background_proc == true){
                //    pids[bg_pid_count++] = child_pid;
                //}
                //else{
                //    
                //}
                child_pid = waitpid(child_pid, &child_exit_status, 0);
                if(WIFEXITED(child_exit_status) != 0){
                    exit_code = WEXITSTATUS(child_exit_status);
                }
                if(WIFSIGNALED(child_exit_status) != 0){
                    exit_code = WTERMSIG(child_exit_status);
                }
                break;
        }
        FreeInput(cmnd_args);
    }
    return 0;
}

        /*********** REMOVE ********************************************************
         *int i;
         *printf("\n(run_shell.c)\nArgs: [%d]\n", arg_count);
         *for(i = 0; i < arg_count; i++){
         *   printf("[%d]: %s [%d]\n", i, cmnd_args[i], (int)strlen(cmnd_args[i]));
         *}
         *printf("\n");
         ******** REMOVE *********************************************************/

        /*********** REMOVE ********************************************************
         *printf("\n(run_shell.c - post processing)\nArgs: [%d]\n", arg_count);
         *for(i = 0; i < arg_count; i++){
         *   printf("[%d]: %s [%d]\n", i, cmnd_args[i], (int)strlen(cmnd_args[i]));
         *}
         *printf("input redir: %s\n", input_redir_file);
         *printf("output redir: %s\n", output_redir_file);
         *printf("\n");
         ********* REMOVE *********************************************************/