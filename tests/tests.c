#include <stdio.h>

// Ignores print statements in parser
#define printf(...) 
#define TEST_PRINT(...) fprintf(stdout, __VA_ARGS__)

#include "..\\src\\cmd_arg_parser.c"

typedef struct {
	int passed;
	char error_str[128];	
} UnitTestResult;

typedef struct {
	char* test_name;
	UnitTestResult (*test_func)();
} UnitTest;

void ValidArgFunc(ArgState* args) {
	args->argi++;
}

void ErrorFunc(ArgState* args) {
	args->argi = -1;
}

UnitTestResult TEST_ParseCommandLineArguments_ValidArg() {
    ArgHandler arg_handlers[1] = {0};

    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ValidArgFunc;

	ArgState args;
	args.argc = 2;
	char* argv[2] = {
		"file_name",
		"-c"
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 1);
	UnitTestResult test_result;
	if(parse_result.argi == -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), parse_result.error_str);
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_NullHandler() {
	ArgState args;
	args.argc = 1;
	char* argv[1] = {
		"file_name",
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, NULL, 1);
	UnitTestResult test_result;
	if(parse_result.argi != -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Handler list was null, but parsing succeeded...\n");
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_ZeroLengthHandlers() {
    ArgHandler arg_handlers[1] = {0};
    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ValidArgFunc;

	ArgState args;
	args.argc = 1;
	char* argv[1] = {
		"file_name",
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 0);
	UnitTestResult test_result;
	if(parse_result.argi != -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Handler length was zero, but parsing succeeded...\n");
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_InvalidArg() {
    ArgHandler arg_handlers[1] = {0};

    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ValidArgFunc;

	ArgState args;
	args.argc = 2;
	char* argv[2] = {
		"file_name",
		"-d"
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 1);
	UnitTestResult test_result;
	if(parse_result.argi != -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Invalid arg passed, but parsing succeeded...\n");
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_ValidAndInvalidArgs() {
    ArgHandler arg_handlers[1] = {0};

    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ValidArgFunc;

	ArgState args;
	args.argc = 3;
	char* argv[3] = {
		"file_name",
		"-c",
		"-d"
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 1);
	UnitTestResult test_result;
	if(parse_result.argi != -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Invalid arg passed, but parsing succeeded...\n");
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_MultipleValidArgs() {
    ArgHandler arg_handlers[2] = {0};

    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ValidArgFunc;

    snprintf(arg_handlers[1].flag, sizeof(arg_handlers[1].flag), "--test");
    arg_handlers[1].FlagFunc = ValidArgFunc;

	ArgState args;
	args.argc = 3;
	char* argv[3] = {
		"file_name",
		"-c",
		"--test"
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 2);
	UnitTestResult test_result;
	if(parse_result.argi == -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), parse_result.error_str);
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

UnitTestResult TEST_ParseCommandLineArguments_HandlerError() {
    ArgHandler arg_handlers[1] = {0};

    snprintf(arg_handlers[0].flag, sizeof(arg_handlers[0].flag), "-c");
    arg_handlers[0].FlagFunc = ErrorFunc;

	ArgState args;
	args.argc = 2;
	char* argv[2] = {
		"file_name",
		"-c"
	};
	args.argv = argv;
	args.argi = 1;

	ArgState parse_result = ParseCommandLineArguments(args, arg_handlers, 1);
	UnitTestResult test_result;
	if(parse_result.argi != -1) {
		test_result.passed = 0;
		snprintf(test_result.error_str, sizeof(test_result.error_str), "Handler threw error, but parsing succeeded...\n");
	}
	else {
		test_result.passed = 1;
	}

	return test_result;
}

int main() {
	#define NUM_TESTS 7
	UnitTest all_tests[NUM_TESTS];

	UnitTest test_0;
	test_0.test_name = "TEST_ParseCommandLineArguments_ValidArg()";
	test_0.test_func =  TEST_ParseCommandLineArguments_ValidArg;
	all_tests[0] = test_0;

	UnitTest test_1;
	test_1.test_name = "TEST_ParseCommandLineArguments_NullHandler()";
	test_1.test_func =  TEST_ParseCommandLineArguments_NullHandler;
	all_tests[1] = test_1;

	UnitTest test_2;
	test_2.test_name = "TEST_ParseCommandLineArguments_ZeroLengthHandlers()";
	test_2.test_func =  TEST_ParseCommandLineArguments_ZeroLengthHandlers;
	all_tests[2] = test_2;

	UnitTest test_3;
	test_3.test_name = "TEST_ParseCommandLineArguments_InvalidArg()";
	test_3.test_func =  TEST_ParseCommandLineArguments_InvalidArg;
	all_tests[3] = test_3;

	UnitTest test_4;
	test_4.test_name = "TEST_ParseCommandLineArguments_ValidAndInvalidArgs()";
	test_4.test_func =  TEST_ParseCommandLineArguments_ValidAndInvalidArgs;
	all_tests[4] = test_4;

	UnitTest test_5;
	test_5.test_name = "TEST_ParseCommandLineArguments_MultipleValidArgs()";
	test_5.test_func =  TEST_ParseCommandLineArguments_MultipleValidArgs;
	all_tests[5] = test_5;

	UnitTest test_6;
	test_6.test_name = "TEST_ParseCommandLineArguments_HandlerError()";
	test_6.test_func =  TEST_ParseCommandLineArguments_HandlerError;
	all_tests[6] = test_6;

	for(int i = 0; i < NUM_TESTS; ++i) {
		TEST_PRINT("Running test %s...", all_tests[i].test_name);
		UnitTestResult test_result = all_tests[i].test_func();
		if(test_result.passed) {
			TEST_PRINT("PASSED\n");
		}
		else {
			TEST_PRINT("FAILED\n");
			TEST_PRINT(test_result.error_str);
		}
	}
}