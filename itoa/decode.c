#include <stdio.h>

int decode(const char* StringNumber, int radix) {

	int result = 0;
	int negativ = 0;
	int c;

	// check radix

	if ((c = *StringNumber++) == '-') {
		negativ = 1;
		c = *StringNumber++;
	} /* endif */

	do {
		if (c >= '0' && c <= '9') {
			c = c - '0';
		}
		else if (c >= 'a' && c <= 'z') {
			c = c - 'a' + 10;
		}
		else if (c >= 'A' && c <= 'Z') {
			c = c - 'A' + 10;
		}
		else {
			fprintf(stderr, "ERROR: %u is not valid\n", c);
		} /* endif */

		  // check overflow!

		result = result * radix + c;

	} while ((c = *StringNumber++) != '\0'); /* enddo */

	return negativ ? -result : result;
}
