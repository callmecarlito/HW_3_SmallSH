#ifndef BUILT_IN_CMNDS
#define BUILT_IN_CMNDS

#include <stdlib.h>

void ExitCmnd(int exit_code);
void ChangeDirCmnd(char* cmnd_args[]);
int StatusCmnd(int stat_code);

#endif 