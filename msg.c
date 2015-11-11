#include "msg.h"

void msg_error(const char* msg)
{
	fprintf(stderr, "ERROR: %s\n", msg);
}

void msg_warning(const char* msg)
{
	fprintf(stderr, "WARNING: %s\n", msg);
}
