//Boyer-Moore string matching algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdint.h>

char *read_file(char *filename) {
	FILE *f = fopen(filename, "r");
	if (!f)abort();

	unsigned long length;
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer) abort();
	fread(buffer, sizeof(char), length, f);
	buffer[length] = '\0';

	return (buffer);
}

int main() {
	//text input
	char *text = read_file("data_5.txt");
	int text_length = strlen(text);

	//user input
	char user_input[100]; user_input[0] = '\0';
	printf("Enter a string: ");
	scanf("%s", user_input);

	char *pattern = malloc(sizeof(char) * (strlen(user_input) + 1));
	strcpy(pattern, user_input);
	int pattern_length = strlen(pattern);

	struct timeb search_start, search_end;
	ftime(&search_start);

	//tables
	int *border_position = malloc(sizeof(int) * (pattern_length + 1));
	int *shift_table = malloc(sizeof(int) * (pattern_length + 1));

	for (int i = 0; i < pattern_length + 1; i++)
		shift_table[i] = 0;

	int k = pattern_length;
	int j = pattern_length + 1;
	border_position[k] = j;
	while (k > 0) {
		while (j <= pattern_length && pattern[k - 1] != pattern[j - 1]) {
			if (shift_table[j] == 0)
				shift_table[j] = j - k;

			j = border_position[j];
		}
		
		k -= 1;
		j -= 1;
		border_position[k] = j;
	}

	j = border_position[0];
	for (int i = 0; i <= pattern_length; i++) {
		if (shift_table[i] == 0)
			shift_table[i] = j;

		if (i == j)
			j = border_position[j];
	}

	int search_count = 0;
	int switch_count = 0;
	int i = 0;
	while (i <= text_length - pattern_length) {
		int j = pattern_length - 1;
		switch_count++;

		while (j >= 0 && pattern[j] == text[i + j])
			j -= 1;
		
		if (j < 0) {
			i += shift_table[0];
			search_count++;
		} else {
			i += shift_table[j + 1];
		}
	}

	ftime(&search_end);

	switch_count -= 1;
	printf("Total matches of user input \"%s\" is %d.\n", user_input, search_count);
	printf("Number of pattern switches: %d\n", switch_count);
	printf("Search Time: [%d ms]\n", search_end.millitm - search_start.millitm);
	
	/* cleanup */
	free(text);
	free(pattern);
	free(border_position);
	free(shift_table);
	return (1);
}