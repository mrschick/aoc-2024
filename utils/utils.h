/*
 * Collection of common utility functions
 */
#include <stdio.h>
#include <limits.h>

/*
 * Simple function to print an array of N elements in the format: "0, 1, 2, 3, ..., N."
 */
void printArray(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		printf("%d, ", *(array + i));
	}
	printf("%d.", *(array + n - 1));
}

/*
 * Simple functions to get the max/min value in an array of integers
 */
int findMin(int* array, int n) {
	int min = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (*(array + i) < min) {
			min = *(array + i);
		}
	}
	return min;
}

int findMax(int* array, int n) {
	int max = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (*(array + i) > max) {
			max = *(array + i);
		}
	}
	return max;
}

/*
 * Radix/Count sorting, useful to sort large arrays of data with multiple digits at a time complexity of O(nk)/O(n+k)
 * Code taken from https://www.geeksforgeeks.org/c-program-for-radix-sort/
 */
void countSort(int* arr, int n, int exp) {
	// output array
	int output[n];
	int i, count[10] = { 0 };
 
	// Store count of occurrences in count[]
	for (i = 0; i < n; i++) {
		count[(arr[i] / exp) % 10]++;
	}
 
	// Change count[i] so that count[i] now contains actual position of this digit in output[]
	for (i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
 
	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
 
	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

void radixSort(int* arr, int n) {
	// Find the maximum number to know number of digits
	int max = findMax(arr, n);
 
	// Do counting sort for every digit.
	for (int exp = 1; max / exp > 0; exp *= 10) {
		countSort(arr, n, exp);
	}
}
