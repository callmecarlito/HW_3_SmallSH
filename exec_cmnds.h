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
void PrintFlags(Shell_Flags* shell_flags);
void SetBuiltInFlag(char* cmnd_args[], Shell_Flags* shell_flags);
int SetStdinRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
int SetStdoutRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
void SetBackgroundFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
char* GetRedirFile(char* cmnd_args[], int index);
void RemoveCmndArgs(char* cmnd_args[], int* arg_count, Shell_Flags* shell_flags);
void RemoveElement(char* cmnd_args[], int* arg_count, int index);
void ExecBuiltIn(char* cmnd_args[], int exit_code);

void ExecuteCmnds(char* cmnd_args[]);
void SetupRedirections(Shell_Flags* shell_flags, char* input_redir_file, char* output_redir_file);

#endif
