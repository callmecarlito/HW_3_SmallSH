#ifndef EXEC_CMNDS
#define EXEC_CMNDS

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct Shell_Flags{
    bool built_in_flag;
    bool stdin_redirect;
    bool stdout_redirect;
    bool background_proc;
} Shell_Flags;

void CmndProcessing(char* cmnd_args[], int arg_count);
void InitializeFlags(Shell_Flags* shell_flags);
void GetFlags(Shell_Flags* shell_flags);
void SetBuiltInFlag(char* cmnd_args[], Shell_Flags* shell_flags);
int SetStdinRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
int SetStdoutRedirFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);
void SetBackgroundFlag(char* cmnd_args[], int arg_count, Shell_Flags* shell_flags);

#endif
