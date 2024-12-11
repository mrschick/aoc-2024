/*
 * https://adventofcode.com/2024/day/3
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

	bool enabled = true;
	unsigned int totalSumPart1 = 0, totalSumPart2 = 0, currentPosition = 0, product = 0, a = 0, b = 0;
	char buffer[SINGLE_CHAR];
	char command[COMMAND_LENGTH];
	while (!feof(inputFile)) {
		// Read new line from file
		if (fgets(buffer, SINGLE_CHAR, inputFile) == NULL) break;

		if (strcmp(buffer, "d") == 0) {
			// Found possible do()/don't() instruction
			currentPosition = ftell(inputFile);
			fseek(inputFile, -1, SEEK_CUR);

			fgets(command, COMMAND_LENGTH, inputFile);
			if (strstr(command, "do()") != NULL) {
				enabled = true;
			} else if (strstr(command, "don't()") != NULL) {
				enabled = false;
			}

			fseek(inputFile, currentPosition, SEEK_SET); // Return FP to after found "m"/"d", to avoid skipping nearby valid records
		} else if (strcmp(buffer, "m") == 0) {
			// Found possible mul(a,b) instruction
			currentPosition = ftell(inputFile);
			fseek(inputFile, -1, SEEK_CUR);

			// Check for "mul(a,b)" pattern via Regex
			fgets(command, COMMAND_LENGTH, inputFile);
			regexReturn = regexec(&regex, command, 3, matches, 0);
			if (regexReturn == 0) {
				a = atoi(command + matches[1].rm_so);
				b = atoi(command + matches[2].rm_so);
				product = (a * b);
				totalSumPart1 += product;
				if (enabled) totalSumPart2 += product;
			}
			fseek(inputFile, currentPosition, SEEK_SET); // Return FP to after found "m"/"d", to avoid skipping nearby valid records
		}
	}

	regfree(&regex);
	fclose(inputFile);

	printf("Part 1 - sum of all mul(a,b) operations: %u\n", totalSumPart1);
	printf("Part 2 - sum of ENABLED mul(a,b) operations: %u\n", totalSumPart2);

	timeEnd = clock();
	printf("\nTotal Execution Time: %f\n", ((double)timeEnd-timeStart)/CLOCKS_PER_MS);

	return 0;
}
