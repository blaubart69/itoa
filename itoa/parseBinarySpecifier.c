#include <stdlib.h>
#include <stdbool.h>

int parseBinarySpecifier(const char* spec, bool leadingZeros, int* width) {
	if (*spec++ != '%') {
		return 1;
	}

	leadingZeros = (*spec == '0');

	if (leadingZeros) {
		spec++;
	}

	return -1;

}