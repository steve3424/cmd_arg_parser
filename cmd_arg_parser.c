#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

int ArgStrExists(char* s) {
	#define NUM_STR_ARGS 2
	char* str_args[NUM_STR_ARGS] = {
		"heythere",
		"buddy"
	};

	for(int i = 0; i < NUM_STR_ARGS; ++i) {
		if(strcmp(s, str_args[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

int ArgCharExists(char c) {
	switch(c) {
		case 'a':
		{
			return 1;
		} break;

		case 'b':
		{
			return 1;
		} break;

		case 'c':
		{
			return 1;
		} break;

		default:
		{
			return 0;
		} break;
	}
}

void InvalidArgumentString(char* s, int i) {
	printf("Invalid arg \"%s\" at pos %d...", s, i);
}

void InvalidArgumentChar(char c, int i) {
	printf("Invalid arg '%c' at pos %d...", c, i);
}

int ParseCommandLineArguments(int argc, char** argv) {
	for(int i = 1; i < argc; ++i) {
		char* arg_string = argv[i];

		if(arg_string[0] != '-') {
			InvalidArgumentString(arg_string, i - 1);
			return 0;
		}
		else if(arg_string[1] == '-') {
			if(arg_string[2] == '\0') {
				printf("Empty arg at pos %d...\n", i - 1);
				return 0;
			}

			// String args
			if(!ArgStrExists(arg_string + 2)) {
				InvalidArgumentString(arg_string + 2, i - 1);
				return 0;
			}
			
			printf("Good arg %s at pos %d...\n", arg_string + 2, i - 1);
		}
		else {
			// Char args
			int j = 1;
			while(arg_string[j]) {
				if(!ArgCharExists(arg_string[j])) {
					InvalidArgumentChar(arg_string[j], i - 1);
					return 0;
				}
				++j;
			}

			if(j == 1) {
				printf("Empty arg at pos %d...\n", i - 1);
				return 0;
			}
			else if(j == 2) {
				printf("Good arg '%s' at pos %d...\n", arg_string + 1, i - 1);
			}
			else {
				printf("Good args '%s' at pos %d...\n", arg_string + 1, i - 1);
			}
		}
	}

	return 1;
}