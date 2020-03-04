//Pre-Sorting algorithm
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/timeb.h>

vector* read_file(char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) abort();

	char buffer[1000]; buffer[0] = '\0';
	char *toAdd = NULL;
	vector* v = malloc(sizeof(vector));
	vector_init(v);

	while (!feof (f)) {
		buffer[0] = '\0';
		fscanf (f, "%s", buffer);
		toAdd = malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(toAdd, buffer);
		vector_add(v, toAdd);
	}

	fclose(f);

	return (v);
}

int compare_chars(const void* a, const void* b) {
	return *(char*)a - *(char*)b;
}

int compare_strings(const void* a, const void* b) {
	return (strcmp(a, b));
}

//must take in a sorted string
bool is_anagram_sorted(char* a, char* b) {
	if (strlen(a) != strlen(b)) return (false);

	for (int i = 0; i < strlen(a); i++) {
		if (a[i] != b[i]) return (false);
	}

	return (true);
}

int main() {
	//get list of all data words
	vector* data = read_file("data_4.txt");

	//user input
	char user_input[100]; user_input[0] = '\0';
	printf("Enter a string: ");
	scanf("%s", user_input);

	char *pattern = malloc(sizeof(char) * (strlen(user_input) + 1));
	strcpy(pattern, user_input);

	//remove duplicate
	for (int i = 0; i < data->total; i++) {
		if (strcmp(data->items[i], user_input) == 0) {
			vector_delete(data, i);
		}
	}

	struct timeb sort_start, sort_end;
	ftime(&sort_start);
	//sort user input signature
	qsort(pattern, strlen(pattern), sizeof(char), compare_chars);

	//sort all data strings into signature
	for (int i = 0; i < data->total; i++) {
		qsort(data->items[i], strlen(data->items[i]), sizeof(char), compare_chars);
	}
	ftime(&sort_end);


	struct timeb search_start, search_end;
	ftime(&search_start);
	unsigned counter = 0;
	for (int i = 0; i < data->total; i++) {
		if (is_anagram_sorted(pattern, vector_get(data, i))){
			counter++;
		}
	}
	ftime(&search_end);

	printf("Total matches for anagrams of user input \"%s\" is %d.\n", user_input, counter);
	printf("Sort Time: [%d ms]\n", sort_end.millitm - sort_start.millitm);
	printf("Search Time: [%d ms]\n", search_end.millitm - search_start.millitm);

	/* cleanup */
	for (int i = 0; i < data->total; i++) free(data->items[i]);
	vector_free(data);
	free(data);
	free(pattern);
	return (1);
}

//qsort(data->items, data->total, sizeof(void*), compare_strings);
/* for (int i = 0; i < data->total; i++) {
	printf("%s\n", (char*)data->items[i]);
} */ //printing utility
