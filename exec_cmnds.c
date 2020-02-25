#include "exec_cmnds.h"


/**********************************************************************
 * InitializeFlags() -
 **********************************************************************/
void InitializeFlags(Shell_Flags* shell_flags){

    shell_flags->built_in_flag = false;
    shell_flags->stdin_redirect = false;
    shell_flags->stdout_redirect = false;
    shell_flags->background_proc = false;
}
/**********************************************************************
 * 
 **********************************************************************/
void GetFlags(Shell_Flags* shell_flags){
    
    printf("built_in_flag: %d\n", shell_flags->built_in_flag);
    printf("stdin_redirect: %d\n", shell_flags->stdin_redirect);
    printf("stdout_redirect: %d\n", shell_flags->stdout_redirect);
    printf("background_proc: %d\n", shell_flags->background_proc);
}
/**********************************************************************
 * 
 **********************************************************************/
void SetBuiltInFlag(char* cmnd_args[], Shell_Flags* shell_flags){
    
    if(strcmp(cmnd_args[0], "exit") == 0 ||
       strcmp(cmnd_args[0], "status") == 0 ||
       strcmp(cmnd_args[0], "cd") == 0){
           shell_flags->built_in_flag = true;
    }
}
/**********************************************************************
 * 
 **********************************************************************/
void SetBackgroundFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags){
    
    if(strcmp(cmnd_args[arg_count-1], "&") == 0){
        shell_flags->background_proc = true;
    }
}
/**********************************************************************
 * 
 **********************************************************************/
int SetStdinRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags){
    int i;

    for(i = 0; i < arg_count; i++){
        if(strcmp(cmnd_args[i], "<") == 0){
            shell_flags->stdin_redirect = true;
            return i+1; //index where stdin is redirected from
        }
    }
    return 0;
}
/**********************************************************************
 * 
 **********************************************************************/
int SetStdoutRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags){
    int i;

    for(i = 0; i < arg_count; i++){
        if(strcmp(cmnd_args[i], ">") == 0){
            shell_flags->stdout_redirect = true;
            return i+1; //index where stdin is redirected from
        }
    }
    return 0;
}
/**********************************************************************
 * 
 **********************************************************************/
char* GetRedirFile(char* cmnd_args[], int index){
    return cmnd_args[index];
}
/**********************************************************************
 * 
 **********************************************************************/
void RemoveCmndArgs(char* cmnd_args[], int* arg_count, Shell_Flags* shell_flags){
    int i, 
        input_index = 0,
        output_index = 0;
    if(shell_flags->background_proc == true){
        cmnd_args[(*arg_count) - 1] = NULL;
        (*arg_count)--;
    }
    if(shell_flags->stdin_redirect == true){
        for(i = 0; i < *arg_count; i++){
            if(strcmp(cmnd_args[i], "<") == 0){
                input_index = i;
                break;
            }
        }
        RemoveElement(cmnd_args, arg_count, input_index);
        RemoveElement(cmnd_args, arg_count, input_index);
    }
    if(shell_flags->stdout_redirect == true){
        for(i = 0; i < *arg_count; i++){
            if(strcmp(cmnd_args[i], ">") == 0){
                output_index = i;
                break;
            }
        }
        RemoveElement(cmnd_args, arg_count, output_index);
        RemoveElement(cmnd_args, arg_count, output_index);
    }    

    
    
}
/**********************************************************************
 * 
 **********************************************************************/
void RemoveElement(char* cmnd_args[], int* arg_count, int index){
    int i;

    for(i = index; i < *arg_count; i ++){
        cmnd_args[i] = cmnd_args[i + 1];
    }
    (*arg_count)--;
}
/**********************************************************************
 * 
 **********************************************************************/
void ExecBuiltIn(char* cmnd_args[], int exit_code){
    //handling of built in commands
    if(strcmp(cmnd_args[0], "status") == 0){

        StatusCmnd(exit_code);
    }
    else if(strcmp(cmnd_args[0], "cd") == 0){

        ChangeDirCmnd(cmnd_args);
    }
    else if(strcmp(cmnd_args[0], "exit") == 0){

        free(cmnd_args[0]);
        ExitCmnd(exit_code);
    }
}
/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/

/**********************************************************************
 * 
 **********************************************************************/