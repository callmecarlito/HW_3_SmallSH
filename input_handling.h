#ifndef INPUT_HANDLING
#define INPUT_HANDLING

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 2048
#define MAX_ARGS 512

int ProcessInput(char* user_input, char* cmnd_args[]);
void InputPrompt();
char* GetInput();
bool ValidCmndLength(char* user_input);
bool IgnoreInput(char* user_input);
void RemoveNewline(char* user_input);
int ParseInput(char* user_input, char* cmnd_args[]);
void FreeInput(char* cmnd_args[]);

#endif