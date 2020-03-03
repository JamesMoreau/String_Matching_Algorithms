//Brute force string match
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

    char* buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer) abort();
	fread(buffer, sizeof(char), length, f);
	buffer[length] = '\0';

	return (buffer);	
}

bool brute_force_string_match(const char* p, const char* t, long int i){
    int pattern_length = strlen(p);
    int count = 0;

    for (int j = 0; j < pattern_length; j++) {
        if (p[j] == t[j + i])
            count++;
    }

    return (count == pattern_length);
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

    //search user_input string in data
    unsigned count = 0;
    unsigned shifts = 0;
	ftime(&search_start);
    for (long int i = 0; i < text_length - pattern_length; i++) {
        bool found = brute_force_string_match(pattern, text, i);
        if (found)
            count++;
        else
            shifts++;
        
    }
    ftime(&search_end);

    printf("Total matches of user input \"%s\" is %d.\n", user_input, count);
    printf("Number of pattern shifts: %d\n", shifts);
	printf("Search Time: [%d ms]\n", search_end.millitm - search_start.millitm);

    free(text);
    free(pattern);
    return (1);
}