#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
	#define EXTENSION ".exe"
#else
	#define EXTENSION ""
#endif

const int BLOCK_SIZE = 1024;
const int BLOCK_COUNT = 1024 * 1024;


void generateFile (char * filename) {
	FILE *fp = fopen(filename, "w+");

	int block[BLOCK_SIZE];
	memset(block, 0, BLOCK_SIZE);

	double i;
	for (i = 0; i < BLOCK_COUNT; i++) {
		fwrite(block, BLOCK_SIZE, 1, fp);
	}

	fclose(fp);
}

int main (int argc, char ** argv) {
	if (argc < 3) {
		printf("ZERO generates <Count> 1GB files.\n");
		printf("Usage: zero%s <Output filename template> <Count>\n", EXTENSION);
		printf("Example:\n");
		printf("> zero%s output_ 5\n", EXTENSION);
		printf("will generate 5 1GB files with names: output_1, output_2, etc...\n");

		return 1;
	}

	char * filename_template = argv[1];

	char *p;
	long count = strtol(argv[2], &p, 10);

	if (errno != 0 || *p != '\0' || count > INT_MAX) {
		printf("Count is too big\n");

		return 1;
	}

	int i;
	clock_t time_begin, time_end;
	double time_spent;
	char filename[sizeof(filename_template) + 50];

	for (i = 0; i < count; i++) {

		time_begin = clock();

		printf("Generating file #%i... ", i + 1);

		sprintf(filename, "%s_%i", filename_template, i + 1);
		generateFile(filename);

		time_end = clock();
		time_spent = (double)(time_end - time_begin) / CLOCKS_PER_SEC;
		printf("%.3f sec.\n", time_spent);
	}

	return 1;
}