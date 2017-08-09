#include <stdio.h>

int main(int argc, char *argv[]) {
	/*
	printf("number of parameters: %d\n", argc);

	for (int i = 0; i < argc; i++) {
		printf("param# %d = %s\n", i, argv[i]);
	}
	*/

	if (argc < 2) {
		fprintf(stderr, "Wasted: mission failed");
		return 1;
	}

	char* conversion;
	if (argc == 3) {
		fprintf(stderr, "sie haben auch einen 2. parameter uebergeben: %s\n", argv[2]);
		conversion = argv[2];
	}
	else {
		conversion = "%d";
	}

	FILE *fileToPrint = fopen(argv[1], "rb");

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