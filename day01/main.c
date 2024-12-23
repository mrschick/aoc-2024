/*
 * https://adventofcode.com/2024/day/1
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../utils/utils.h"

#define CLOCKS_PER_MS CLOCKS_PER_SEC/1000
#define LINE_NUM 1000

int main(int argc, char *argv[]) {
	// Benchmarking
	clock_t timeStart, timeParse, timeSort, timeEnd;
	timeStart = clock();

	// Open Input File
	FILE* inputFile = fopen("input.txt", "r");
	if (inputFile == NULL) {
		printf("Could not open input file.");
		return 1;
	}

	// Fetch Data from File
	int left[LINE_NUM];
	int right[LINE_NUM];
	int num = 0;
	char buffer[20];
	do {
		if (fgets(buffer, 6, inputFile) == NULL) break;
		left[num] = (int) strtol(buffer, NULL, 10);
		fseek(inputFile, 3, SEEK_CUR);
		fgets(buffer, 7, inputFile);
		right[num] = (int) strtol(buffer, NULL, 10);
		num++;
	} while (!feof(inputFile));

	printf("Parsed %d file lines.\n\n", num);
	fclose(inputFile);
	timeParse = clock();

	// Sort Arrays
	radixSort(left, num);
	radixSort(right, num);
	timeSort = clock();

	// Find Proof of Part 1
	int total_distance = 0;
	int diff;
	for (int i = 0; i < num; i++) {
		diff = abs(right[i] - left[i]);
		total_distance += diff;
	}

	printf("TOTAL DISTANCE: %d\n", total_distance);

	// Find Proof of Part 2
	int similarity_score = 0;
	bool found = false;
	int right_occurences; // How many times left[i] appears in right[]
	for (int i = 0; i < num; i++) {
		found = false;
		right_occurences = 0;
		for (int j = 0; j < num; j++) {
			if (left[i] == right[j]) {
				right_occurences++;
				found = true;
			} else if (found) {
				// Since the array is already sorted, we can break out as soon as we stop finding duplicates to save time
				break;
			}
		}
		similarity_score += (left[i] * right_occurences);
	}

	printf("SIMILARITY SCORE: %d\n", similarity_score);

	timeEnd = clock();
	printf("\nFile Parsing Time: %fms, Sorting Time: %fms, Proof Time: %fms\nTotal Execution Time: %f\n", ((double)timeParse-timeStart)/CLOCKS_PER_MS, ((double)timeSort-timeParse)/CLOCKS_PER_MS, ((double)timeEnd-timeParse)/CLOCKS_PER_MS, ((double)timeEnd-timeStart)/CLOCKS_PER_MS);

	return 0;
}
