#include "exec_cmnds.h"

/**********************************************************************
 * InitializeFlags() - Sets all flags to false
 **********************************************************************/
void InitializeFlags(Shell_Flags* shell_flags){

    shell_flags->built_in_flag = false;
    shell_flags->stdin_redirect = false;
    shell_flags->stdout_redirect = false;
    shell_flags->background_proc = false;
}
/**********************************************************************
 * PrintFlags() - Prints all flag values
 **********************************************************************/
void PrintFlags(Shell_Flags* shell_flags){
    
    printf("built_in_flag: %d\n", shell_flags->built_in_flag);
    printf("stdin_redirect: %d\n", shell_flags->stdin_redirect);
    printf("stdout_redirect: %d\n", shell_flags->stdout_redirect);
    printf("background_proc: %d\n", shell_flags->background_proc);
}
/**********************************************************************
 * SetBuiltInFlag() - Checks first command argument to see if it matches
 * a built-in command. Sets flag to true if a match is found.
 **********************************************************************/
void SetBuiltInFlag(char* cmnd_args[], Shell_Flags* shell_flags){
    
    if(strcmp(cmnd_args[0], "exit") == 0 ||
       strcmp(cmnd_args[0], "status") == 0 ||
       strcmp(cmnd_args[0], "cd") == 0){
           shell_flags->built_in_flag = true;
    }
}
/**********************************************************************
 * SetBackgroundFlag)() - Checks last element for "&" and if it's there
 * sets flag to true
 **********************************************************************/
void SetBackgroundFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags){
    
    if(strcmp(cmnd_args[arg_count-1], "&") == 0){
        shell_flags->background_proc = true;
    }
}
/**********************************************************************
 * SetStdinRedirFlag() - Searches for "<" and if found, sets flag to true
 * and returns the index location of the file to be redirected to
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
 * SetStdoutRedirFlag() - Searches for ">" and if found, sets flag to true
 * and returns the index location of the file to be redirected to
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
 * GetRedirFile() - returns the string value for the file to which 
 * stdin or stdout will be redirected to
 **********************************************************************/
char* GetRedirFile(char* cmnd_args[], int index){
    return cmnd_args[index];
}
/**********************************************************************
 * RemoveCmndArgs() - Removes any and all arguments related to 
 * stdin and stdout redirections contained in the array
 **********************************************************************/
void RemoveCmndArgs(char* cmnd_args[], int* arg_count, Shell_Flags* shell_flags){
    int i, 
        input_index = 0,
        output_index = 0;

    if(shell_flags->background_proc == true){ //removes the "&"
        cmnd_args[(*arg_count) - 1] = NULL;
        (*arg_count)--;
    }
    if(shell_flags->stdin_redirect == true){ //removes stdin operator "<" and the file to be redirected to
        for(i = 0; i < *arg_count; i++){
            if(strcmp(cmnd_args[i], "<") == 0){
                input_index = i;
                break;
            }
        }
        RemoveElement(cmnd_args, arg_count, input_index); //removes "<"
        RemoveElement(cmnd_args, arg_count, input_index); //removes file name
    }
    if(shell_flags->stdout_redirect == true){ //removes stdout operator ">" and the file to be redirected to
        for(i = 0; i < *arg_count; i++){
            if(strcmp(cmnd_args[i], ">") == 0){
                output_index = i;
                break;
            }
        }
        RemoveElement(cmnd_args, arg_count, output_index); //removes ">"
        RemoveElement(cmnd_args, arg_count, output_index); //removes file name
    }    
}
/**********************************************************************
 * RemoveElement() - Used by RemoveCmndArgs() to delete an element in 
 * the array containing the command arguments
 **********************************************************************/
void RemoveElement(char* cmnd_args[], int* arg_count, int index){
    int i;

    for(i = index; i < *arg_count; i ++){
        cmnd_args[i] = cmnd_args[i + 1];
    }
    (*arg_count)--;
}
/**********************************************************************
 * ExecBuiltIn() - Executes the built-in commands implemented in 
 * built_in_cmnds.h and built_in_cmnds.c files
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
void RedirectionHandler(Shell_Flags* shell_flags, char* input_redir_file, char* output_redir_file){
    char* devnull_file = "/dev/null";

    if(shell_flags->background_proc == true){
        //redirect stdin
        SetupStdinRedir(devnull_file);
        //redirect stdout
        SetupStdoutRedir(devnull_file);
    }
    if(shell_flags->stdin_redirect == true){
        SetupStdoutRedir(input_redir_file);
    }
    if(shell_flags->stdout_redirect == true){
        SetupStdoutRedir(output_redir_file);
    }
}
/**********************************************************************
 * 
 **********************************************************************/
void SetupStdinRedir(char* target_file){
    int target_fd = open(target_file, O_RDONLY);

    if(target_fd == -1){
        perror("Error opening input file: ");
        exit(1); //exit child process with code 1
    }
    else{
        int redir_result = dup2(target_fd, 0);
        if(redir_result == -1){
            perror("Error with dup2() of input file: ");
            exit(1); //exit child process with code 1
        }
    }
    //set fd flags so that the target_fd should be closed when execvp() is invoked
    fcntl(target_fd, F_SETFD, FD_CLOEXEC);
}
/**********************************************************************
 * 
 **********************************************************************/
void SetupStdoutRedir(char* target_file){
    int target_fd = open(target_file, O_WRONLY | O_CREAT | O_TRUNC);

    if(target_fd == -1){
        perror("Error opening output file: ");
        exit(1);
    }
    else{
        int redir_result = dup2(target_fd, 1);
        if(redir_result == -1){
            perror("Error with dup2() of output file: ");
            exit(1);
        }
    }
    //set fd flags so that the target_fd should be closed when execvp() is invoked
    fcntl(target_fd, F_SETFD, FD_CLOEXEC);
}
/**********************************************************************
 * 
 **********************************************************************/
void ForegroundProcHandler(pid_t child_pid, int* status_code){
    int child_exit_status = -5;

    //blocks parent process until child (foreground process) terminates
    child_pid = waitpid(child_pid, &child_exit_status, 0); 
    if(WIFEXITED(child_exit_status) != 0){
        *status_code = WEXITSTATUS(child_exit_status);
    }
    if(WIFSIGNALED(child_exit_status) != 0){
        *status_code = WTERMSIG(child_exit_status);
    }
}
/**********************************************************************
 * 
 **********************************************************************/
void BackgroundProcHandler(pid_t child_pid, pid_t* pids, int* bg_pid_count, int* status_code){
    int child_exit_status = -5;

    pid_t actual_pid = waitpid(child_pid, &child_exit_status, WNOHANG);
    if(actual_pid == -1){
        perror("Error with waitpid(): ");
        //pids[bg_pid_count++] = child_pid; //will attempt to check child_pid again
    }
    else if(actual_pid == 0){
        pids[(*bg_pid_count)++] = child_pid; //no change of state has occurred in child, will need to check again
    }
    else{
        //analyze and set exit code
        if(WIFEXITED(child_exit_status) != 0){
            *status_code = WEXITSTATUS(child_exit_status);
        }
        if(WIFSIGNALED(child_exit_status) != 0){
            *status_code = WTERMSIG(child_exit_status);
        }
    }
}
/**********************************************************************
 * 
 **********************************************************************/
void CheckBgProcesses(pid_t* pids, int* bg_pid_count, int* status_code){
    int i = 0;
    int child_exit_status = -5;

    while(i != *bg_pid_count){
        pid_t actual_pid = waitpid(pids[i], &child_exit_status, WNOHANG);
        if(actual_pid == -1){
            perror("Error with waitpid(): ");
            //pids[bg_pid_count++] = child_pid; //will attempt to check child_pid again
        }
        else{
            if(WIFEXITED(child_exit_status) != 0){
                *status_code = WEXITSTATUS(child_exit_status);
            }
            if(WIFSIGNALED(child_exit_status) != 0){
                *status_code = WTERMSIG(child_exit_status);
            }
            RemoveProcess(pids, bg_pid_count, i);
            continue;
        }
        i++;
    }
}
/**********************************************************************
 * 
 **********************************************************************/
void RemoveProcess(pid_t* pids, int* bg_pid_count, int index){
    int i;

    for(i = index; i < *bg_pid_count; i++){
        pids[i] = pids[i + 1];
    }
    (*bg_pid_count)--;
}
