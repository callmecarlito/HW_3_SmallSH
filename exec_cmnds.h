#ifndef EXEC_CMNDS
#define EXEC_CMNDS

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "built_in_cmnds.h"

typedef struct Shell_Flags{
    bool built_in_flag;
    bool stdin_redirect;
    bool stdout_redirect;
    bool background_proc;
} Shell_Flags;

void InitializeFlags(Shell_Flags* shell_flags);
void GetFlags(Shell_Flags* shell_flags);
void SetBuiltInFlag(char* cmnd_args[], Shell_Flags* shell_flags);
int SetStdinRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
int SetStdoutRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
void SetBackgroundFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);

char* SetInputRedir(char* cmnd_args[], int input_index);
char* SetOutputRedir(char* cmnd_args[], int output_index);
void RemoveCmndArgs(char* cmnd_args[], int* arg_count, int remove_index);
void RemoveBackgroundArg(char* cmnd_args[], int* arg_count);

void ExecBuiltIn(char* cmnd_args[], int exit_code);
void ExecuteCmnds(char* cmnd_args[]);


#endif
