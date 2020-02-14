#include "input_handling.h"
/**********************************************************************
 * GetInput() - reads user input from stdin and returns a string
 **********************************************************************/
char* GetInput(){
    int num_chars_entered = -5;
    //int curr_char = -5;
    size_t input_buffer = 0;
    char* user_input = NULL;

    printf("Enter input (CTRL-C to exit): ");
        fflush(stdout);
        num_chars_entered = getline(&user_input, &input_buffer, stdin);
        if(num_chars_entered == -1){ 
            clearerr(stdin); //clear stdin in case error occurs
            return NULL;
        }
        else{
            //replace newline character with null terminator
            (user_input)[strcspn(user_input, "\n")] = '\0';
            printf("input: %s[%d]\n", user_input, (int)strlen(user_input)); 
            fflush(stdout);
            return user_input;
        }
}

            
            
 
           
    
    