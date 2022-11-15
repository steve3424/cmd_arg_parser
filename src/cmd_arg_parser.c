#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct {
	int    argc;
	char** argv;
	int    argi;
	char error_str[128];
} ArgState;

typedef struct {
    char flag[64];
    void (*FlagFunc)(ArgState*);
} ArgHandler;

ArgState ParseCommandLineArguments(ArgState args, ArgHandler* arg_handlers, int num_handlers) {
	if(!arg_handlers || num_handlers == 0) {
		snprintf(args.error_str, sizeof(args.error_str), "No arg handlers found!");
		args.argi = -1;	
		return args;
	}

	while(args.argi < args.argc) {
		int arg_handler_found = 0;
		for(int i = 0; i < num_handlers; ++i) {
			if(strcmp(args.argv[args.argi], arg_handlers[i].flag) == 0) {
				if(!arg_handlers[i].FlagFunc) {
					args.argi = -1;
					snprintf(args.error_str, sizeof(args.error_str), "Valid arg '%s' found has no handler! Please initialize this flag with handler!\n", arg_handlers[i].flag);
					return args;
				}

				arg_handlers[i].FlagFunc(&args);
				if(args.argi == -1) {
					return args;
				}

				arg_handler_found = 1;
				break;
			}
		}

		if(!arg_handler_found) {
			snprintf(args.error_str, sizeof(args.error_str), "Unrecognized arg '%s' found at position %d\n", args.argv[args.argi], args.argi - 1);
			args.argi = -1;
			return args;
		}
	}

	return args;
}