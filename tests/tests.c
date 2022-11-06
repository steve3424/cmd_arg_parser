#include <stdio.h>

// Ignores print statements in parser
#define printf(...) 
#define TEST_PRINT(...) fprintf(stdout, __VA_ARGS__)

#include "cmd_arg_parser.c"

typedef struct {
	char* test_name;
	int (*test_func)();
} UnitTest;

int TEST_ParseCommandLineArguments_NoArguments() {
	int argc = 1;
	char* argv[1] = {
		"file_name"
	};

	return ParseCommandLineArguments(argc, argv) == 1;
}

int TEST_ParseCommandLineArguments_ValidCharArg() {
	int argc = 2;
	char* argv[2] = {
		"file_name",
		"-a"
	};

	return ParseCommandLineArguments(argc, argv) == 1;
}

int TEST_ParseCommandLineArguments_InvalidCharArg() {
	int argc = 2;
	char* argv[2] = {
		"file_name",
		"-["
	};

	return ParseCommandLineArguments(argc, argv) == 0;
}

int TEST_ParseCommandLineArguments_MultipleValidCharArgs() {
	int argc = 3;
	char* argv[3] = {
		"file_name",
		"-a",
		"-b",
	};

	return ParseCommandLineArguments(argc, argv) == 1;
}

int TEST_ParseCommandLineArguments_MultipleCharArgsOneInvalid() {
	int argc = 3;
	char* argv[3] = {
		"file_name",
		"-a",
		"-[",
	};

	return ParseCommandLineArguments(argc, argv) == 0;
}

int TEST_ParseCommandLineArguments_ValidStringArg() {
	int argc = 2;
	char* argv[2] = {
		"file_name",
		"--heythere",
	};

	return ParseCommandLineArguments(argc, argv) == 1;
}

int TEST_ParseCommandLineArguments_InvalidStringArg() {
	int argc = 2;
	char* argv[2] = {
		"file_name",
		"--notgood",
	};

	return ParseCommandLineArguments(argc, argv) == 0;
}

int main() {
	#define NUM_TESTS 7
	UnitTest all_tests[NUM_TESTS];

	UnitTest test_0;
	test_0.test_name = "TEST_ParseCommandLineArguments_NoArguments()";
	test_0.test_func =  TEST_ParseCommandLineArguments_NoArguments;
	all_tests[0] = test_0;
	// UnitTest test_1;
	// test_1.test_name = "TEST_ParseCommandLineArguments_ValidCharArg()";
	// test_1.test_func =  TEST_ParseCommandLineArguments_ValidCharArg;
	// all_tests[1] = test_1;
	// UnitTest test_2;
	// test_2.test_name = "TEST_ParseCommandLineArguments_InvalidCharArg()";
	// test_2.test_func =  TEST_ParseCommandLineArguments_InvalidCharArg;
	// all_tests[2] = test_2;
	// UnitTest test_3;
	// test_3.test_name = "TEST_ParseCommandLineArguments_MultipleValidCharArgs()";
	// test_3.test_func =  TEST_ParseCommandLineArguments_MultipleValidCharArgs;
	// all_tests[3] = test_3;
	// UnitTest test_4;
	// test_4.test_name = "TEST_ParseCommandLineArguments_MultipleCharArgsOneInvalid()";
	// test_4.test_func =  TEST_ParseCommandLineArguments_MultipleCharArgsOneInvalid;
	// all_tests[4] = test_4;
	// UnitTest test_5;
	// test_5.test_name = "TEST_ParseCommandLineArguments_ValidStringArg()";
	// test_5.test_func =  TEST_ParseCommandLineArguments_ValidStringArg;
	// all_tests[5] = test_5;
	// UnitTest test_6;
	// test_6.test_name = "TEST_ParseCommandLineArguments_InvalidStringArg()";
	// test_6.test_func =  TEST_ParseCommandLineArguments_InvalidStringArg;
	// all_tests[6] = test_6;

	for(int i = 0; i < NUM_TESTS; ++i) {
		TEST_PRINT("Running test %s...", all_tests[i].test_name);
		int passed = all_tests[i].test_func();
		if(passed) {
			TEST_PRINT("PASSED\n");
		}
		else {
			TEST_PRINT("FAILED\n");
		}
	}
}