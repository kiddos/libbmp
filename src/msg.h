#ifndef MSG_H
#define MSG_H

#include <stdio.h>
#include <stdarg.h>

// macro check for null string and immediately return

#define MSG_IS_NULL_STRING(str, status)   \
	if (!str)                             \
	{                                     \
		msg_error("null string pointer"); \
		return status;                    \
	}                                     \

void msg_error(const char* msg);
void msg_error_line(const char* msg, unsigned int n, ...);
void msg_warning(const char* msg);
void msg_warning_line(const char* msg, unsigned int n, ...);

#endif /* end of include guard: MSG_H */
