#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "itoa.h"

#define BUF_READ_SIZE 1024 * 1000

void printUsage(const char* programname);
void printFileBytes_branchInLoop(const char* buffer, const int size, const bool isBinarySpecifier, const char* formatString);
void printFileBytes_loopWithoutBranchInside(const char* buffer, const int size, const bool isBinarySpecifier, const char* formatString);

int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "please enter a filename as first parameter\n");
		printUsage(argv[0]);
		return 1;
	}

	if (argc > 4) {
		fprintf(stderr, "to many parameters given\n");
		printUsage(argv[0]);
		return 1;
	}

	char* conversion;
	if (argc >= 3) {
		fprintf(stderr, "you have entered a 2nd parameter: %s\n", argv[2]);
		conversion = argv[2];
	}
	else {
		conversion = "%d";
	}

	char version = 'b';
	if (argc >= 4) {
		if (argv[3][0] == 'n') {
			version = 'n';
		}
	}

	FILE *fileToPrint = fopen(argv[1], "rb");
	if (fileToPrint == NULL) {
		fprintf(stderr, "error opening file");
		return 2;
	}

	char formatString[32];
	sprintf(formatString, "%s\n", conversion);

	char* binary = isBinarySpecifier(formatString);
	if (binary != NULL) {
		*binary = 's';
	}

	char *buf = malloc(BUF_READ_SIZE);
	int bytesRead;
	while ((bytesRead = fread(buf, sizeof(char), BUF_READ_SIZE, fileToPrint)) != 0) {
		if (version == 'b') {
			printFileBytes_branchInLoop(buf, bytesRead, binary != NULL, formatString);
		}
		else {
			printFileBytes_loopWithoutBranchInside(buf, bytesRead, binary != NULL, formatString);
		}
	}
	free(buf);
	fclose(fileToPrint);

	return 0;
}

void printFileBytes_branchInLoop(const char* buffer, const int size, const bool isBinarySpecifier, const char* formatString) {
	
	for (int i = 0; i < size; i++) {

		int oneByte = buffer[i];

		if (isBinarySpecifier) {
			char binaryString[128];
			_itoa(oneByte, binaryString, 2);
			printf(formatString, binaryString);
		}
		else {
			printf(formatString, oneByte);
		}
	}
}

void printFileBytes_loopWithoutBranchInside(const char* buffer, const int size, const bool isBinarySpecifier, const char* formatString) {
	
	if (isBinarySpecifier) {

		for (int i = 0; i < size; i++) {
			char oneByte = buffer[i];
			char binaryString[128];
			_itoa(oneByte, binaryString, 2);
			printf(formatString, binaryString);
		}
	}
	else {
		for (int i = 0; i < size; i++) {
			char oneByte = buffer[i];
			printf(formatString, oneByte);
		}
	}
}


void printUsage(const char* programname) {
	fprintf(stderr, "usage: %s filename [format]\n", programname);
	fprintf(stderr, "   format ... printf format specifiers. sample: %%02X, %%d, ...\n");
}