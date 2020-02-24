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
char* SetInputRedir(char* cmnd_args[], int input_index){
    return cmnd_args[input_index];
}
/**********************************************************************
 * 
 **********************************************************************/
char* SetOutputRedir(char* cmnd_args[], int output_index){
    return cmnd_args[output_index];
}
/**********************************************************************
 * 
 **********************************************************************/
void RemoveCmndArgs(char* cmnd_args[], int* arg_count, int remove_index){
    int current_element = remove_index,
        next_element = remove_index + 1;
    
    if(remove_index == (*arg_count - 1)){
        cmnd_args[remove_index] = NULL;
    }
    while(cmnd_args[next_element] != NULL){
        cmnd_args[current_element] = cmnd_args[next_element];
        current_element = next_element;
        next_element++;
    }
    (*arg_count)--;
}
/**********************************************************************
 * 
 **********************************************************************/
void RemoveBackgroundArg(char* cmnd_args[], int* arg_count){

    cmnd_args[*arg_count - 1] = NULL;
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