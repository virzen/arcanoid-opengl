//Created by dopieralad on 2018/04/26.

#include <cstdio>
#include <cstdlib>
#include "errors.h"

void Errors::opengl_error_callback(int exit_code, const char* details) {
	handle_fatal(exit_code, details);
}

void Errors::handle_fatal(const char* details) {
	handle_fatal(EXIT_FAILURE, details);
}

void Errors::handle_fatal(const int exit_code, const char* details) {
	fprintf(stderr, details);
	exit(exit_code);
}
