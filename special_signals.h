#ifndef SPECIAL_SIGNALS
#define SPECIAL_SIGNALS

#include <signal.h>
#include <stdbool.h>

void ForegroundOnlySignal(bool foreground_only);

#endif