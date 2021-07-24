#include "util.h"
#include <stdarg.h>

static char msgbuf[512];

void
fatal(const char *fmt, ...)
{
	//cleanup();

	va_list va;
	va_start(va, fmt);
	vsnprintf(msgbuf, sizeof(msgbuf), fmt, va);
	va_end(va);

	fprintf(stderr, "\nFatal error: %s\n", msgbuf);

	//error_dialog(msgbuf);
}