#include <stdio.h>

int main(int argc, char *argv[]) {
	/*
	printf("number of parameters: %d\n", argc);

	for (int i = 0; i < argc; i++) {
		printf("param# %d = %s\n", i, argv[i]);
	}
	*/

	if (argc < 2) {
		fprintf(stderr, "please specify a filename");
		return 1;
	}

	FILE *fileToPrint = fopen(argv[1], "rb");

	int oneByte;
	while ( (oneByte = fgetc(fileToPrint)) != EOF) {
		printf("%d\n", oneByte);
	}

	fclose(fileToPrint);

	return 0;
}