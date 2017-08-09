#include <stdio.h>

void printUsage(const char* programname);

int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "please enter a filename as first parameter\n");
		printUsage(argv[0]);
		return 1;
	}

	if (argc > 3) {
		fprintf(stderr, "to many parameters given\n", argv[3]);
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

	FILE *fileToPrint = fopen(argv[1], "rb");
	if (fileToPrint == NULL) {
		fprintf(stderr, "filename does not exist");
		return 2;
	}

	char formatString[32];
	sprintf(formatString, "%s\n", conversion);

	int oneByte;
	while ( (oneByte = fgetc(fileToPrint)) != EOF) {
		//printf("%d\n", oneByte);
		printf(formatString, oneByte);
	}

	fclose(fileToPrint);

	return 0;
}

void printUsage(const char* programname) {
	fprintf(stderr, "usage: %s filename [format]\n", programname);
	fprintf(stderr, "   format ... printf format specifiers. sample: %%02X, %%d, ...\n");
	fprintf(stderr, "   format ... printf format specifiers. sample: °/o02X, °/od, ...\n");
}