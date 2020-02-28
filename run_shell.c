#include "input_handling.h"
#include "exec_cmnds.h"
#include "special_signals.h"

#define MAX_PIDS 20 //set to 20, can adjust accordingly

int main(){

    char* user_input = NULL; //variable will contain initial input from user
    char* cmnd_args[MAX_ARGS]; //array containing the parsed user input
    int arg_count = -5; //variable holding the number of parsed arguments
    Shell_Flags shell_flags; //struct of shell_flags used for processing commands

    pid_t child_pid = -5; //variable containg most recently fork child pid
    int status_code = -5;  //contains most recently set status code

    pid_t pids[MAX_PIDS]; //array containing background pid's
    int bg_pid_count = 0; //keeps count of the number of elements in the array

    memset(cmnd_args, '\0', sizeof(memset)); //clear memory to be used for args array
    memset(pids, '\0', sizeof(pids)); //clear memory to be used for pids array

    bool foreground_only = false;

    //infinitie while loop 
    while(1){
        //check (background)pids for terminated/exitted child process
        //remove from pids array
        //print exit status of last terminated child process
        if(bg_pid_count > 0){
            CheckBgProcesses(pids, &bg_pid_count, &status_code);
        }
        //if after last call to CheckBgProcess and no child
        //if(bg_pid_count == MAX_PIDS){continue;}
        //get user input and process input into separate arguments
        arg_count = ProcessInput(user_input, cmnd_args);
        //if there's an error that occurs in ProcessInput() it will return 0
        //and will return to the top of the loop to re-attempt getting user input
        if(arg_count <= 0){continue;}
        //
        if(foreground_only && (strcmp(cmnd_args[arg_count - 1], "&") == 0)){
            RemoveElement(cmnd_args, &arg_count, arg_count - 1); //remove & at the end before setting flags
        }
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
            ExecBuiltIn(cmnd_args, status_code); //execution of built-in commands
            free(cmnd_args[0]); //free allocated memory
            continue;
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
        child_pid = fork(); //create child process
        switch(child_pid){
            case -1: //case of error
                perror("Fork error: "); exit(1); break;
            case 0: //child process
                //print pid of backgroud/child process before executing cmnds
                if(shell_flags.background_proc == true){ 
                    printf("Background pid is: %d\n", getpid()); fflush(stdout); 
                }
                //Setup any redirections
                RedirectionHandler(&shell_flags, input_redir_file, output_redir_file);
                //execute non built-in commands
                execvp(cmnd_args[0], cmnd_args);
                //if error occurs with excvp()
                perror("Execvp() error: "); free(cmnd_args[0]); exit(1); break;
            default: //parent process
                sleep(1);
                if(shell_flags.background_proc == true){
                    //add child_pid to array, will call waitpid() before next user input prompt
                    pids[bg_pid_count++] = child_pid;
                    //BackgroundProcHandler(child_pid, pids, &bg_pid_count, &status_code);
                }
                else{
                    //blocks parent process until child (foreground process) terminates and sets status_code
                    ForegroundProcHandler(child_pid, &status_code);
                }
                break;
        }
        FreeInput(cmnd_args); //free allocated memory
    }
    return 0;
}        