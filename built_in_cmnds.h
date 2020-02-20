#ifndef BUILT_IN_CMNDS
#define BUILT_IN_CMNDS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ExitCmnd(int exit_code);
void ChangeDirCmnd(char* cmnd_args[]);
int StatusCmnd(int stat_code);

#endif 