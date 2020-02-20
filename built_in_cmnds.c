#include "built_in_cmnds.h"

/**********************************************************************
 * ExitCmnd() - 
 **********************************************************************/
void ExitCmnd(int exit_code){
    exit(exit_code);
}
/**********************************************************************
 * ChangeDirCmnd() - 
 **********************************************************************/
void ChangeDirCmnd(char* cmnd_args[]){
    int cd_status;
    char dir_path[256];
    //size_t path_buffer = 0;

    if(cmnd_args[1] == NULL || strcmp(cmnd_args[1], "~") == 0){
        cd_status = chdir(getenv("HOME"));
        if(cd_status == -1){
            perror("Change directory error: ");
        }
    }
    else{
        cd_status = chdir(cmnd_args[1]);
        if(cd_status == -1){
            perror("Change directory error: ");
        }
    }
    getcwd(dir_path, sizeof(dir_path));
    printf("%s\n", dir_path);
    //free(dir_path);
}
/**********************************************************************
 * CurrentStatus() -
 **********************************************************************/
int StatusCmnd(int stat_code){
    return 0;
}