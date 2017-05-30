/**
 *	These functions will print the given message just like printf
 *	if DEBUG_ENABLED is 1. They will print the message with keywords
 *	"Warning: ", "Message: ", and "Error: " at the beginning.
 
 *	@author Ural Bayhan
 */

#ifndef __DEBUG_H
#define __DEBUG_H

#define DEBUG_ENABLED 1 //Debug value to know if we are in debug

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int debugPrintWarning(char* s, ...);
int debugPrintMessage(char* s, ...);
int debugPrintError(char* s, ...);

#endif
