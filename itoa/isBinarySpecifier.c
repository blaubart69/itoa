#include <stdio.h>

char* isBinarySpecifier(const char* spec) {

	if (*spec != '%') {
		return NULL;
	}

	do {
		spec++;
	} while ((*spec >= '\0' && *spec <= '9') || *spec == '-' );

	if (spec != NULL && *spec == 'b') {
		return spec;
	}

	return NULL;
}