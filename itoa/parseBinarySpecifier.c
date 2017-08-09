#include <stdlib.h>

int parseBinarySpecifier(const char* spec, char* leadingZeros, int* width) {
	if (*spec++ != '%') {
		return 1;
	}

	leadingZeros = (*spec == '0') ? 1 : 0;

	if (leadingZeros) {
		spec++;
	}

	atoi()

}