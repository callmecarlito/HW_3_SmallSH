#include "input_handling.h"

/**********************************************************************
 *  
 **********************************************************************/
void ProcessInput(char* user_input, char* cmnd_args[]){

}
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
        if(num_chars_entered < 0){ 
            clearerr(stdin); //clear stdin in case error occurs
            return NULL;
        }
        else{
            //replace newline character with null terminator
            printf("input: %s[%d]\n", user_input, (int)strlen(user_input)); 
            fflush(stdout);
            return user_input;
        }
}
/**********************************************************************
 * ValidCmndLength() - 
 **********************************************************************/
bool ValidCmndLength(char* user_input){
    if(strlen(user_input) < MAX_LENGTH){
        return true;
    }
    else{
        return false;
    }
}
/**********************************************************************
 *  
 **********************************************************************/     
bool IgnoreInput(char* user_input){

}
/**********************************************************************
 *  
 **********************************************************************/
void RemoveNewline(char* user_input){
    (user_input)[strcspn(user_input, "\n")] = '\0';
}
/**********************************************************************
 *  
 **********************************************************************/
void ParseInput(char* user_input, char* cmnd_args[]){
    
}
/**********************************************************************
 *  
 **********************************************************************/
bool ValidNumArgs(char* cmnd_args[]){

}
           
    
    