#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_handling.h"

int main(){

    int num_chars_entered = -5;
    int curr_char = -5;
    size_t input_buffer = 0;
    char* user_input = NULL;

    while(1){
        while(1){
            printf("Enter input (CTRL-C to exit): ");
            num_chars_entered = getline(&user_input, &input_buffer, stdin);
            if(num_chars_entered == -1){
                clearerr(stdin);
            }
            if(strcmp(user_input, "exit\n") == 0){
                printf("Exiting\n");
                free(user_input);
                exit (0);
            }
            else{
                printf("\tentered: %s\n", user_input);
                break;
            }
        }
        
    }
    free(user_input);
    return 0;
}