#include <stdio.h>
#include <stdlib.h>

#include "itoa.h"

void printUsage(const char* programname);

int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "please enter a filename as first parameter\n");
		printUsage(argv[0]);
		return 1;
	}

	if (argc > 3) {
		fprintf(stderr, "to many parameters given\n");
		printUsage(argv[0]);
		return 1;
	}

	char* conversion;
	if (argc == 3) {
		fprintf(stderr, "you have entered a 2nd parameter: %s\n", argv[2]);
		conversion = argv[2];
	}
	else {
		conversion = "%d";
	}

	FILE *fileToPrint;
	errno_t rc = fopen_s(&fileToPrint, argv[1], "rb");
	if (rc != 0) {
		fprintf(stderr, "error opening file. rc=%d", rc);
		return 2;
	}

	char formatString[32];
	sprintf(formatString, "%s\n", conversion);

	char* binary = isBinarySpecifier(formatString);
	if (binary != NULL) {
		*binary = 's';
	}

	int oneByte;
	while ( (oneByte = fgetc(fileToPrint)) != EOF) {
		if (binary) {
			char binaryString[128];
			_itoa(oneByte, binaryString, 2);
			printf(formatString, binaryString);
		}
		else {
			printf(formatString, oneByte);
		}
	}

	fclose(fileToPrint);

	return 0;
}

void printUsage(const char* programname) {
	fprintf(stderr, "usage: %s filename [format]\n", programname);
	fprintf(stderr, "   format ... printf format specifiers. sample: %%02X, %%d, ...\n");
}