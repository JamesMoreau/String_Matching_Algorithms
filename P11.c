//Brute Force Anagram
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/timeb.h>

//input function
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

bool is_anagram(char* a, char* b) {
    int frequency_a[10] = {0};
    int frequency_b[10] = {0};

	if (strlen(a) != strlen(b)) return (false);

	for (int i = 0; i < strlen(a); i++) {
		frequency_a[a[i] - '0']++;
	}

	for (int i = 0; i < strlen(b); i++) {
		frequency_b[b[i] - '0']++;
	}

	for (int i = 0; i < 10; i++) {
		if (frequency_a[i] != frequency_b[i])
			return (false);
	}
	
    return true;
}

int main() {
	//get list of all data words
	vector* data = read_file("data_4.txt");

	//user input
	char user_input[100]; user_input[0] = '\0';
	printf("Enter a string: ");
	scanf("%s", user_input);

	struct timeb t_start, t_end;

	//search and compare the data for equivelant anagram strings
    ftime(&t_start);
	unsigned match_count = 0;
	for (int i = 0; i < data->total; i++) {
		if (strcmp(vector_get(data, i), user_input) &&
			is_anagram(vector_get(data, i), user_input)) {
			match_count++;
		}
	}
    ftime(&t_end);

	printf("Total matches for anagrams of user input \"%s\" is %d.\n", user_input, match_count);
	printf("Search Time: [%d ms]\n", t_end.millitm - t_start.millitm);

	/* cleanup */
	for (int i = 0; i < data->total; i++) free(data->items[i]);
	vector_free(data);
	free(data);
	return (1);
}