#include "input_handling.h"
#include "built_in_cmnds.h"

int main(){
    char* user_input = NULL;
    char* cmnd_args[MAX_ARGS];
    int arg_count = -5;

    int i;


    while(1){
        
        arg_count = ProcessInput(user_input, cmnd_args);

        /*********** REMOVE *******************************/
        printf("\n(run_shell.c)\nArgs: [%d]\n", arg_count);
        for(i = 0; i < arg_count; i++){
            printf("[%d]: %s\n", i, cmnd_args[i]);
        }
        printf("\n");
        /*********** REMOVE *******************************/

        if(arg_count <= 0){
            continue;
        }

        //handling of built in commands
        if(strcmp(cmnd_args[0], "status") == 0){
            int status_code = 123;

            StatusCmnd(status_code);
        }
        else if(strcmp(cmnd_args[0], "cd") == 0){
            ChangeDirCmnd(cmnd_args);
        }
        else if(strcmp(cmnd_args[0], "exit") == 0){
            int exit_code = 123;

            FreeInput(cmnd_args);
            ExitCmnd(exit_code);
        }
        else{
            /* code */
        }
        
        FreeInput(cmnd_args);
    }
    return 0;
}