#include "input_handling.h"

/**********************************************************************
 *  ProcessInput() - main driving function for prompting, reading, and
 *  processing user input
 **********************************************************************/
int ProcessInput(char* user_input, char* cmnd_args[]){
    
    while(user_input == NULL){
        InputPrompt(); //displays prompt to user
        user_input = GetInput(); //reads input from stdin
        //makes sure input doesn't exceed 2048 chars
        if(!ValidCmndLength(user_input)){
            free(user_input);
            user_input = NULL;
            continue;
        }
        //ignores blank lines and inputs beginning with "#"
        if(IgnoreInput(user_input)){
            free(user_input);
            user_input = NULL;
            continue;
        }
        //replaces newline with null terminator
        RemoveNewline(user_input);
        //parses input which is necessary for executing arguments
        //returns number of arguments
        return ParseInput(user_input, cmnd_args);
    }
    return 0;
}
/**********************************************************************
 * InputPrompt() - Displays input prompt within terminal
 **********************************************************************/
void InputPrompt(){

    printf(": ");
    fflush(stdout);
}
/**********************************************************************
 * GetInput() - reads user input from stdin and returns a string
 **********************************************************************/
char* GetInput(){
    int num_chars_entered = -5;
    //int curr_char = -5;
    size_t input_buffer = 0;
    char* user_input = NULL;

    //getline allocates memory for input
    //REMEMBER TO FREE MEMORY!!!!
    num_chars_entered = getline(&user_input, &input_buffer, stdin);
    if(num_chars_entered < 0){ 
        clearerr(stdin); //clear stdin in case error occurs
        return NULL;
    }
    else{
        return user_input;
    }
}
/**********************************************************************
 * ValidCmndLength() - makes sure input doesn't exceed 2048 chars and 
 * returns true if input is below the limit
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
 * IgnoreInput() - ignores empty lines and inputs beginning with "#"
 **********************************************************************/     
bool IgnoreInput(char* user_input){

    if(strcmp(user_input, "\n") == 0){
        //printf("ignore newline\n");
        return true;
    }
    if(strncmp(user_input, "#", 1) == 0){
        //printf("ignore newline\n");
        return true;
    }
    else{
        return false;
    }
}
/**********************************************************************
 * RemoveNewline() - replaces newline char with null terminator
 **********************************************************************/
void RemoveNewline(char* user_input){

    (user_input)[strcspn(user_input, "\n")] = '\0';
}
/**********************************************************************
 * ParseInput() - parses the input into arguments and the pointers to 
 * each argument are stored in the array
 **********************************************************************/
int ParseInput(char* user_input, char* cmnd_args[]){
    int arg_count = 0;
    char* arg;

    //parses input using strtok() delimited by whitespace(s)
    arg = strtok(user_input, " ");    
    while(arg != NULL && arg_count < MAX_ARGS){
        cmnd_args[arg_count++] = arg; //stores pointer to argument in array
        arg = strtok(NULL, " ");
    }
    if(arg_count >= MAX_ARGS){ //if MMAX_ARGS is exceeded
        free(user_input);
        user_input = NULL;
        arg_count = 0;
    }
    cmnd_args[arg_count] = NULL;
    return arg_count;
}
/**********************************************************************
 * FreeArgs() - frees the memory allocated by getline()
 **********************************************************************/
void FreeInput(char* cmnd_args[]){
    
    free(cmnd_args[0]);
}
           
    
    