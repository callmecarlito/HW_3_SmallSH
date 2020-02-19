#include "input_handling.h"

/**********************************************************************
 *  ProcessInput() - 
 **********************************************************************/
int ProcessInput(char* user_input, char* cmnd_args[]){
    
    while(user_input == NULL){
        InputPrompt();
        user_input = GetInput();
        if(!ValidCmndLength(user_input)){
            free(user_input);
            user_input = NULL;
            continue;
        }
        if(IgnoreInput(user_input)){
            free(user_input);
            user_input = NULL;
            continue;
        }
        RemoveNewline(user_input);

        //printf("input: %s[%d]\n", user_input, (int)strlen(user_input)); 
        //fflush(stdout);
        
        return ParseInput(user_input, cmnd_args);
    }
    return 0;
}
/**********************************************************************
 * InputPrompt() - 
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
 * IgnoreInput() - 
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
 * RemoveNewline()
 **********************************************************************/
void RemoveNewline(char* user_input){

    (user_input)[strcspn(user_input, "\n")] = '\0';
}
/**********************************************************************
 * ParseInput()
 **********************************************************************/
int ParseInput(char* user_input, char* cmnd_args[]){
    int arg_count = 0;
    char* arg;

    arg = strtok(user_input, " ");    
    while(arg != NULL && arg_count < MAX_ARGS){
        cmnd_args[arg_count++] = arg;
        arg = strtok(NULL, " ");
    }
    if(arg_count >= MAX_ARGS){
        free(user_input);
        user_input = NULL;
        arg_count = 0;
    }
    return arg_count;
}
/**********************************************************************
 * FreeArgs() -
 **********************************************************************/
void FreeInput(char* cmnd_args[]){
    
    free(cmnd_args[0]);
}
           
    
    