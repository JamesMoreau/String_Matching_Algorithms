//Horspool's algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/timeb.h>

char* read_file(char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) abort();

	unsigned long length;
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	//TODO \0
	char* buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer) abort();
	fread(buffer, sizeof(char), length, f);
	buffer[length] = '\0';

	fclose(f);
	return (buffer);	
}

void horspool_shift_table(char* p, int table[]) {
	int pattern_length = strlen(p);

	for (int i = 0; i < 500; i++) {
		table[i] = pattern_length;
	}

	for (int j = 0; j < pattern_length - 1; j++) {
		table[p[j]] = pattern_length - j - 1;
	}
}

int main() { 
	char* text = read_file("data_5.txt");
	long int text_length = strlen(text);

	//user input
	char user_input[100]; user_input[0] = '\0';
	printf("Enter a string: ");
	scanf("%s", user_input);
	
	char* pattern = malloc(sizeof(char) * (strlen(user_input) + 1));
	strcpy(pattern, user_input);
	int pattern_length = strlen(pattern);

	struct timeb search_start, search_end;
	ftime(&search_start);

	//Horspool's alogrithm
	int table[500] = {0};
	horspool_shift_table(pattern, table);

	int found_count = 0;
	int shifts = 0;
	long int i = 0;
	while (i < text_length - pattern_length) {
		int new_i = text[i + pattern_length - 1];
		if (new_i < 0) {
			i++;
			new_i = text[i + pattern_length - 1];
		}

		if (
			pattern[pattern_length - 1] == new_i && 
			memcmp(pattern, text + i, pattern_length - 1) == 0
			) found_count++;

		shifts++;
		i += table[new_i];
	}

	ftime(&search_end);

	printf("Total matches of user input \"%s\" is %d.\n", user_input, found_count);
	printf("Number of pattern shifts: %d\n", shifts);
	printf("Search Time: [%d ms]\n", search_end.millitm - search_start.millitm);

	/* Cleanup */
	free(text);
	free(pattern);
	return (1);
}