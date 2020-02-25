#include "input_handling.h"
#include "exec_cmnds.h"

int main(){
    char* user_input = NULL; //variable will contain initial input from user
    char* cmnd_args[MAX_ARGS]; //array containing the parsed user input
    int arg_count = -5; //variable holding the number of parsed arguments
    Shell_Flags shell_flags; //struct of shell_flags used for processing commands
    int exit_code = -5; 

    //infinitie while loop 
    while(1){
        //get user input and process input into separate arguments
        arg_count = ProcessInput(user_input, cmnd_args);
        //if there's an error that occurs in ProcessInput() it will return 0
        //and will return to the top of the loop to re-attempt getting user input
        if(arg_count <= 0){
            continue;
        }
        /*********** REMOVE ********************************************************/
        int i;
        printf("\n(run_shell.c)\nArgs: [%d]\n", arg_count);
        for(i = 0; i < arg_count; i++){
           printf("[%d]: %s [%d]\n", i, cmnd_args[i], (int)strlen(cmnd_args[i]));
        }
        printf("\n");
        /********* REMOVE *********************************************************/
        int input_redir_index = 0; //holds index number for the location of "<" in the array
        int output_redir_index = 0; //holds index number for the location of ">" in the array
        char* input_redir_file = NULL; //holds value for where input redirection will occur
        char* output_redir_file = NULL; //holds value for where output redirection will occur
        
        InitializeFlags(&shell_flags); //initialize all flags to false
        SetBuiltInFlag(cmnd_args, &shell_flags); //if the 0th element refers to a built-in command, this will set the flag true
        SetBackgroundFlag(cmnd_args, arg_count, &shell_flags); //if the last element contains "&", this will set flag true
        input_redir_index = SetStdinRedirFlag(cmnd_args, arg_count, &shell_flags); //if "<" is found, flag will be set true, and the index location will be returned
        output_redir_index = SetStdoutRedirFlag(cmnd_args, arg_count, &shell_flags); //if ">" is found, flag will be set true, and the index location will be returned
        
        /*********** REMOVE ********************************************************/
        GetFlags(&shell_flags);
        /*********** REMOVE ********************************************************/

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

        /*********** REMOVE ********************************************************/
        printf("\n(run_shell.c - post processing)\nArgs: [%d]\n", arg_count);
        for(i = 0; i < arg_count; i++){
           printf("[%d]: %s [%d]\n", i, cmnd_args[i], (int)strlen(cmnd_args[i]));
        }
        printf("input redir: %s\n", input_redir_file);
        printf("output redir: %s\n", output_redir_file);
        printf("\n");
        /********* REMOVE *********************************************************/
        FreeInput(cmnd_args);
    }
    return 0;
}