/*
 * https://adventofcode.com/2024/day/2
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define CLOCKS_PER_MS CLOCKS_PER_SEC/1000
#define MAX_REPORT_NUMS 20
#define MAX_LINE_LENGTH 30

// Check if a report is safe
bool isReportSafe(int *line, int num) {
	bool lineIncreasing = (line[0] < line[num-1]);

	for (int i = 1; i < num; i++) {
		if (
			line[i-1] == line[i] || 
			(line[i-1] < line[i]) != lineIncreasing || 
			abs(line[i-1] - line[i]) > 3
		) {
			return false;
		}
	}

	return true;
}

// Function to try removing one level to make a report safe
bool tryProblemDampener(int *line, int num) {
	int modifiedLine[MAX_REPORT_NUMS];

	for (int i = 0; i < num; i++) {
		int modifiedIndex = 0;

		// Create a new report excluding the current level
		for (int j = 0; j < num; j++) {
			if (j != i) {
				modifiedLine[modifiedIndex++] = line[j];
			}
		}

		// Check if the modified report is safe
		if (isReportSafe(modifiedLine, modifiedIndex)) {
			return true; // Problem Dampener succeeded
		}
	}

	return false; // None of the modified reports are safe
}

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
	unsigned int reportSafeCounter = 0;
	unsigned int reportUnsafeCounter = 0;
	char buffer[MAX_LINE_LENGTH];
	char *pch;
	int line[MAX_REPORT_NUMS] = { 0 };
	short lineIndex;
	bool safe;
	while (!feof(inputFile)) {
		// Read new line from file
		if (fgets(buffer, MAX_LINE_LENGTH, inputFile) == NULL) break;

		lineIndex = 0;
		pch = strtok(buffer, " ");
		while (pch != NULL) {
			line[lineIndex++] = strtol(pch, NULL, 10);
			pch = strtok(NULL, " ");
		}

		// Part 1, determine whether each report is safe or unsafe
		safe = isReportSafe(line, lineIndex);
		if (!safe) {
			// Part 2, check whether an unsafe report can be made safe by removing a single element
			safe = tryProblemDampener(line, lineIndex);
		}

		if (safe) {
			reportSafeCounter++;
		} else {
			reportUnsafeCounter++;
		}
	}

	fclose(inputFile);

	printf("Safe Records: %d\nUnsafe Records: %d\n", reportSafeCounter, reportUnsafeCounter);

	timeEnd = clock();
	printf("\nTotal Execution Time: %f\n", ((double)timeEnd-timeStart)/CLOCKS_PER_MS);

	return 0;
}
