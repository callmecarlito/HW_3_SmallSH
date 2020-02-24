#include "input_handling.h"
#include "exec_cmnds.h"

int main(){
    char* user_input = NULL;
    char* cmnd_args[MAX_ARGS];
    int arg_count = -5;
    Shell_Flags shell_flags;
    int input_redir_index = 0, 
        output_redir_index = 0;
    int exit_code = -5;
    char* input_redir_file = NULL;
    char* output_redir_file = NULL;


    while(1){
        
        arg_count = ProcessInput(user_input, cmnd_args);

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

        //initialize flags
        InitializeFlags(&shell_flags);
        SetBuiltInFlag(cmnd_args, &shell_flags);
        SetBackgroundFlag(cmnd_args, arg_count, &shell_flags);
        input_redir_index = SetStdinRedirFlag(cmnd_args, arg_count, &shell_flags);
        output_redir_index = SetStdoutRedirFlag(cmnd_args, arg_count, &shell_flags);
        
        GetFlags(&shell_flags);

        if(shell_flags.built_in_flag == true){
            ExecBuiltIn(cmnd_args, exit_code);
        }
        //get redirection info
        
        /*********** REMOVE ********************************************************/
        int i;
        printf("\n(run_shell.c - post processing)\nArgs: [%d]\n", arg_count);
        for(i = 0; i < arg_count; i++){
           printf("[%d]: %s [%d]\n", i, cmnd_args[i], (int)strlen(cmnd_args[i]));
        }
        printf("\n");
        /********* REMOVE *********************************************************/
        FreeInput(cmnd_args);
    }
    return 0;
}