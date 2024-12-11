/*
 * https://adventofcode.com/2024/day/3
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>

#define CLOCKS_PER_MS CLOCKS_PER_SEC/1000
#define SINGLE_CHAR 2 // String with space for 1 char + NULL terminator
#define COMMAND_LENGTH 13

int main(int argc, char *argv[]) {
	// Benchmarking
	clock_t timeStart, timeEnd;
	timeStart = clock();

	// Open Input File
	FILE* inputFile = fopen("input.txt", "r");
	if (inputFile == NULL) {
		printf("Could not open input file.\n");
		return 1;
	}

	// Process Data from File
	regex_t regex;
	if (regcomp(&regex, "^mul\\(([0-9]+),([0-9]+)\\).*$", REG_EXTENDED) != 0) {
		printf("Failed to compile regex\n");
		return 1;
	}
	regmatch_t matches[3];
	int regexReturn;

	unsigned int totalSum = 0, currentPosition = 0;
	short a = 0, b = 0;
	char buffer[SINGLE_CHAR];
	char command[COMMAND_LENGTH];
	while (!feof(inputFile)) {
		// Read new line from file
		if (fgets(buffer, SINGLE_CHAR, inputFile) == NULL) break;

		// Skip to next Char until the pattern's first Char is found
		if (strcmp(buffer, "m") != 0) continue;
		currentPosition = ftell(inputFile);
		fseek(inputFile, -1, SEEK_CUR);

		// Check for "mul(a,b)" pattern
		fgets(command, COMMAND_LENGTH, inputFile);
		//printf("Testing input: %s\n", command);
		regexReturn = regexec(&regex, command, 3, matches, 0);
		if (regexReturn == 0) {
			a = atoi(command + matches[1].rm_so);
			b = atoi(command + matches[2].rm_so);
			//printf("Matched items, a: %d, b: %d\n", a, b);
			totalSum += (a * b);
		}
		fseek(inputFile, currentPosition, SEEK_SET); // Return FP to after found "m", to avoid skipping nearby valid records
	}

	regfree(&regex);
	fclose(inputFile);

	printf("Final sum of all mul(a,b) operations: %u\n", totalSum);

	timeEnd = clock();
	printf("\nTotal Execution Time: %f\n", ((double)timeEnd-timeStart)/CLOCKS_PER_MS);

	return 0;
}
