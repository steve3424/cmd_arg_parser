#include "cmd_arg_parser.c"

int main(int argc, char** argv) {
    if(ParseCommandLineArguments(argc, argv)) {
        printf("Good job!\n");
    }
    else {
        printf("Bad job!\n");
    }
}