#include "input_handling.h"
#include "built_in_cmnds.h"

int main(){
    char* user_input = NULL;
    char* cmnd_args[MAX_ARGS];
    int arg_count = 0;

    int i;


    while(1){
        
        arg_count = ProcessInput(user_input, cmnd_args);

        printf("Args: [%d]\n", arg_count);
        for(i = 0; i < arg_count; i++){
            printf("[%d]: %s\n", i, cmnd_args[i]);
        }

        if(strcmp(cmnd_args[0], "exit") == 0){ 
            printf("Exiting\n");
            FreeInput(cmnd_args);
            exit(0);
        }
        
        FreeInput(cmnd_args);
    }
    return 0;
}