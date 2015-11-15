#include "msg.h"

void msg_error(const char* msg)
{
	fprintf(stderr, "ERROR: %s\n", msg);
}

void msg_warning(const char* msg)
{
	fprintf(stderr, "WARNING: %s\n", msg);
}

void msg_error_line(const char* msg, unsigned int n, ...)
{
	va_list args;
	va_start(args, n);
	fprintf(stderr, "ERROR: %s", msg);

	unsigned int i;
	for (i = 0 ; i < n ; i++)
		fprintf(stderr, " %s", va_arg(args, const char*));

	va_end(args);
}

void msg_warning_line(const char* msg, unsigned int n, ...)
{
	va_list args;
	va_start(args, n);
	fprintf(stderr, "WARNING: %s", msg);

	unsigned int i;
	for (i = 0 ; i < n ; i++)
		fprintf(stderr, " %s", va_arg(args, const char*));

	va_end(args);
}
