#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[]) {
	Status(*tests[])(char*, int) = { test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_jgaul_test_my_string_compare_prefix_word,
		test_jgaul_test_my_string_compare_identical_word,
		test_jgaul_test_my_string_compare_same_size_words,
		test_jgaul_test_my_string_test_get_size,
		test_jgaul_test_my_string_test_get_capacity,
		test_jgaul_my_string_destroy_sets_handle_NULL,
		test_jgaul_init_string_default_has_capacity_7,
		test_jgaul_pop_back_increments_string_size,
		test_jgaul_pop_back_handles_empty_string,
		test_jgaul_my_string_at_returns_correct_char,
		test_jgaul_my_string_at_handles_negative_index,
		test_jgaul_my_string_at_handles_index_too_large,
		test_jgaul_my_string_init_c_string_has_correct_size,
		test_jgaul_my_string_extraction_gets_word_correctly,
		test_jgaul_my_string_extract_has_proper_capacity,
		test_jgaul_my_string_extract_has_proper_size,
		test_jgaul_my_string_empty_on_empty_string,
		test_jgaul_my_string_empty_on_filled_string,
		test_jgaul_my_string_insertion_inerts_correctly,
		test_jgaul_my_string_concat_has_correct_result,
		test_jgaul_my_string_concat_has_correct_status,
		test_jgaul_my_string_insertion_invalid_file,
		test_jgaul_my_string_extraction_invalid_file
	};

	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;


	for (i = 0; i < number_of_functions; i++) {
		if (tests[i](buffer, 500) == FAILURE) {
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else {
			// printf("PASS: Test %d passed\n", i);
			// printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
		number_of_functions, failure_count, number_of_functions);
	return 0;
}
