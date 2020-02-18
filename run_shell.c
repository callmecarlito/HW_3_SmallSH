#include "input_handling.h"
#include "built_in_cmnds.h"

int main(){
        char* user_input = NULL;
    while(1){
        user_input = GetInput();
        printf("%s\n", user_input);
        if(ValidCmndLength(user_input)){
            printf("Command is of valid length\n");
            fflush(stdout);
        }
        if(strcmp(user_input, "exit\n") == 0){ /************ REMOVE "\n" **********/
            printf("Exiting\n");
            free(user_input);
            exit(0);
        } 
        free(user_input);
    }
    return 0;
}