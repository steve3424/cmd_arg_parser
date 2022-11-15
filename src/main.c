#include "cmd_arg_parser.c"

// HANDLER FUNCTIONS
void DashCFunc(ArgState* args) {
    printf("Called %s func with flag %s...\n", __func__, args->argv[args->argi]);
    int next_argi = args->argi + 1;
    if(next_argi == args->argc) {
        snprintf(args->error_str, sizeof(args->error_str), "Expecting argument after '-c' flag...\n");
        args->argi = -1;
        return;
    }

    if(strcmp(args->argv[next_argi], "hey") == 0) {
        args->argi = next_argi + 1;
    }
    else {
        snprintf(args->error_str, sizeof(args->error_str), "Unrecognized argument '%s' after '-c' flag...\n", args->argv[next_argi]);
        args->argi = -1;
        return;
    }
}

void DashDFunc(ArgState* args) {
    printf("Called %s func with flag %s...\n", __func__, args->argv[args->argi]);
    args->argi++;
}

void HelpFunc(ArgState* args) {
    printf("I can't help right now...\n");
    args->argi++;
}

// INIT FUNCTION
void InitArgHandlers(ArgHandler* arg_handlers) {
    memcpy(arg_handlers[0].flag, "-c", 3);
    arg_handlers[0].FlagFunc = DashCFunc;

    memcpy(arg_handlers[1].flag, "-d", 3);
    arg_handlers[1].FlagFunc = DashDFunc;

    memcpy(arg_handlers[2].flag, "--help", 7);
    arg_handlers[2].FlagFunc = HelpFunc;
}

int main(int argc, char** argv) {
    ArgHandler arg_handlers[3] = {0};
    InitArgHandlers(arg_handlers);
    ArgState args = {
        .argc = argc,
        .argv = argv,
        .argi = 1
    };
    ArgState args_parsed = ParseCommandLineArguments(args, arg_handlers, sizeof(arg_handlers) / sizeof(ArgHandler));
    if(args_parsed.argi == -1) {
        printf(args_parsed.error_str);
    }
}