#include "input_handling.h"

int main(){
        char* user_input = NULL;
    while(1){
        user_input = GetInput();
        printf("%s\n", user_input);
        if(strcmp(user_input, "exit") == 0){
            printf("Exiting\n");
            free(user_input);
            exit(0);
        } 
        free(user_input);
    }
    return 0;
}