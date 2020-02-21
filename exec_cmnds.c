#include "exec_cmnds.h"

/**********************************************************************
 * 
 **********************************************************************/
void CmndProcessing(char* cmnd_args[], int arg_count){
    int input_redir_index = 0, 
        output_redir_index = 0;

    Shell_Flags shell_flags;
    InitializeFlags(&shell_flags);

    SetBuiltInFlag(cmnd_args, &shell_flags);
    SetBackgroundFlag(cmnd_args, arg_count, &shell_flags);
    input_redir_index = SetStdinRedirFlag(cmnd_args, arg_count, &shell_flags);
    output_redir_index = SetStdoutRedirFlag(cmnd_args, arg_count, &shell_flags);
    
    GetFlags(&shell_flags);
    
}
/**********************************************************************
 * InitializeFlags() -
 **********************************************************************/
void InitializeFlags(Shell_Flags* shell_flags){

    shell_flags->built_in_flag = 0;
    shell_flags->stdin_redirect = 0;
    shell_flags->stdout_redirect = 0;
    shell_flags->background_proc = 0;
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