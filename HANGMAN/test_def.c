#include "unit_test.h"
#include "my_string.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length) {
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString == NULL) {
		my_string_destroy(&hString);
		strncpy(buffer, "my_string_init_default returns NULL", length);
		return FAILURE;
	}
	else {
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if (my_string_get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n" 
			"Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			, length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_jgaul_test_my_string_compare_prefix_word(char* buffer, int length) {
	MY_STRING hMy_string_1 = my_string_init_c_string("Computer");
	MY_STRING hMy_string_2 = my_string_init_c_string("Computers");
	Status failType = SUCCESS;
	if (my_string_compare(hMy_string_1, hMy_string_2) >= 0 || my_string_compare(hMy_string_2, hMy_string_1) <= 0) {
		failType = FAILURE;
	}
	my_string_destroy(&hMy_string_1);
	my_string_destroy(&hMy_string_2);
	if (!failType) {
		strncpy(buffer, "test_jgaul_test_my_string_compare_prefix_word\n"
			"my_string_compare returned a shorter string as lexicographically greater or equal\n", length);
	}
	else {
		strncpy(buffer, "test_jgaul_test_my_string_compare_prefix_word\n"
			"my_string_compare returned the correct value\n", length);
	}

	return failType;
}


Status test_jgaul_test_my_string_compare_identical_word(char* buffer, int length) {
	MY_STRING hMy_string_1 = my_string_init_c_string("Computer");
	MY_STRING hMy_string_2 = my_string_init_c_string("Computer");
	if ((my_string_compare(hMy_string_1, hMy_string_2) | my_string_compare(hMy_string_2, hMy_string_1)) == 0) {
		strncpy(buffer, "test_jgaul_test_my_string_compare_identical_word\n"
			"my_string_compare returned zero for identical strings\n", length);
		my_string_destroy(&hMy_string_1);
		my_string_destroy(&hMy_string_2);
		return SUCCESS;
	} else {
		strncpy(buffer, "test_jgaul_test_my_string_compare_identical_word\n"
			"my_string_compare returned a nonzero value for identical strings\n", length);
		my_string_destroy(&hMy_string_1);
		my_string_destroy(&hMy_string_2);
		return FAILURE;
	}
}

Status test_jgaul_test_my_string_compare_same_size_words(char* buffer, int length) {
	MY_STRING hMy_string_1 = my_string_init_c_string("Computer");
	MY_STRING hMy_string_2 = my_string_init_c_string("Computed");
	if (my_string_compare(hMy_string_1, hMy_string_2) <= 0 || my_string_compare(hMy_string_2, hMy_string_1) >= 0) {
		my_string_destroy(&hMy_string_1);
		my_string_destroy(&hMy_string_2);
		strncpy(buffer, "test_jgaul_test_my_string_compare_same_size_words\n"
			"my_string_compare returned a lexicographically greater string as greater\n", length);
		return FAILURE;
	}
	else {
		my_string_destroy(&hMy_string_1);
		my_string_destroy(&hMy_string_2);
		strncpy(buffer, "test_jgaul_test_my_string_compare_same_size_words\n"
			"my_string_compare returned a lexicographically lesser string as greater or 0\n", length);
		return SUCCESS;
	}
}

Status test_jgaul_test_my_string_test_get_size(char* buffer, int length) {
	int i;
	char str[200];
	MY_STRING hMy_string_1 = my_string_init_c_string("Test string");

	if ((i = my_string_get_size(hMy_string_1)) == 11) {
		strncpy(buffer, "test_jgaul_test_my_string_test_get_size\n"
			"my_string_get_size returned the correct size\n", length);
		my_string_destroy(&hMy_string_1);
		return SUCCESS;
	}
	else {
		sprintf(str, "test_jgaul_test_my_string_test_get_size\n"
			"my_string_get_size returned the wrong size: %d\n", i);
		strncpy(buffer, str, length);
		my_string_destroy(&hMy_string_1);
		return FAILURE;
	}
}

Status test_jgaul_test_my_string_test_get_capacity(char* buffer, int length) {
	int i;
	char str[200];
	MY_STRING hMy_string_1 = my_string_init_default();
	if ((i = my_string_get_capacity(hMy_string_1)) == 7) {
		strncpy(buffer, "test_jgaul_test_my_string_test_get_capacity\n"
			"my_string_get_capacity returned the correct capacity\n", length);
		my_string_destroy(&hMy_string_1);
		return SUCCESS;
	}
	else {
		sprintf(str, "test_jgaul_test_my_string_test_get_capacity\nmy_string_get_size returned the wrong capacity: %d\n", i);
		strncpy(buffer, str, length);
		my_string_destroy(&hMy_string_1);
		return FAILURE;
	}
}

Status test_jgaul_my_string_destroy_sets_handle_NULL(char* buffer, int length) {
	MY_STRING hString = my_string_init_c_string("Lorem Ipsum");
	my_string_destroy(&hString);
	if (hString) {
		strncpy(buffer, "test_jgaul_my_string_destroy_sets_handle_NULL\n"
			"The string handle was not set to NULL\n", length);
		return FAILURE;
	}
	else {
		strncpy(buffer, "test_jgaul_my_string_destroy_sets_handle_NULL\n"
			"The string handle was set to null.\n", length);
		return SUCCESS;
	}
}

Status test_jgaul_init_string_default_has_capacity_7(char* buffer, int length) {
	int i;
	char str[200];
	MY_STRING hMy_string_1 = my_string_init_default();
	if ((i = my_string_get_capacity(hMy_string_1)) == 7) {
		strncpy(buffer, "test_jgaul_init_string_default_has_capacity_7\n"
			"Default string capcity is 7\n", length);
		my_string_destroy(&hMy_string_1);
		return SUCCESS;
	}
	else {
		sprintf(str, "test_jgaul_init_string_default_has_capacity_7\n"
			"default string capacity is: %d\n", i);
		strncpy(buffer, str, length);
		my_string_destroy(&hMy_string_1);
		return FAILURE;
	}
}

Status test_jgaul_push_back_doubles_string_capacity(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("Capacity is 16");
	my_string_push_back(string, '!');
	my_string_push_back(string, '?');
	if (my_string_get_capacity(string) == 32) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_push_back_doubles_string_capacity\n"
			"my_string_push_back doubled string capacity\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_push_back_doubles_string_capacity\n"
			"my_string_push_back did not double string capacity\n", length);
		return FAILURE;
	}
}


Status test_jgaul_pop_back_increments_string_size(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("Size is 10");
	my_string_pop_back(string);
	if (my_string_get_size(string) == 9) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_pop_back_increments_string_size\n"
			"my_string_pop_back doubled string capacity\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_pop_back_increments_string_size\n"
			"my_string_pop_back doubled string capacity\n", length);
		return FAILURE;
	}
}

Status test_jgaul_pop_back_handles_empty_string(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("");

	if (!my_string_pop_back(string)) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_pop_back_handles_empty_string\n"
			"my_string_pop_back handled empty string\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_pop_back_handles_empty_string\n"
			"my_string_pop_back failed with empty string\n", length);
		return FAILURE;
	}
}

Status test_jgaul_my_string_at_returns_correct_char(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("abcdefghijk");
	if (*my_string_at(string, 2) == 'c') {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_returns_correct_char\n"
			"my_string_at returned correct char\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_returns_correct_char\n"
			"my_string_at returned incorrect char\n", length);
		return FAILURE;
	}
}

Status test_jgaul_my_string_at_handles_negative_index(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("abcdefghijk");

	if (my_string_at(string, -5) == NULL) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_handles_negative_index\n"
			"my_string_at returned NULL on a negative index\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_handles_negative_index\n"
			"my_string_at failed to return a NULL value for a negative index\n", length);
		return FAILURE;
	}
}


Status test_jgaul_my_string_at_handles_index_too_large(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("abcdefghijk");

	if (my_string_at(string, 100) == NULL) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_handles_index_too_large\n"
			"my_string_at returned NULL on an index that caused overflow\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_at_handles_index_too_large\n"
			"my_string_at failed to return a NULL value for an index that caused overflow\n", length);
		return FAILURE;
	}
}
Status test_jgaul_my_string_init_c_string_has_correct_size(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("Hello");

	if (my_string_get_size(string) == 5) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_init_c_string_has_correct_size\n"
			"my_string_get_size returned correct value\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_init_c_string_has_correct_size\n"
			"my_string_get_size returned incorrect size\n", length);
		return FAILURE;
	}
}
Status test_jgaul_my_string_extraction_gets_word_correctly(char* buffer, int length) {
	FILE* fp;
	fp = fopen("testing_in.txt", "r");
	if (!fp) {
		strncpy(buffer, "Failed to open file: testing_in.txt\n", length); return FAILURE; }
	else {
		MY_STRING string = my_string_init_default();
		my_string_extraction(string, fp);
		my_string_extraction(string, fp);
		fclose(fp);
		if (*my_string_at(string, 0) == 'a' && *my_string_at(string, 2) == 'e') {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extraction_gets_word_correctly\n"
				"my_string_extraction extracted the correct word with no whitespace\n", length);
			return SUCCESS;

		}
		else {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extraction_gets_word_correctly\n"
				"my_string_extraction did not extract the correct word with no whitespace\n", length);
			return FAILURE;
		}
	}
}
Status test_jgaul_my_string_extract_has_proper_capacity(char* buffer, int length) {
	FILE* fp;
	fp = fopen("testing_in.txt", "r");
	if (!fp) {
		strncpy(buffer, "Failed to open file: testing_in.txt\n", length); return FAILURE;
	}
	else {
		MY_STRING string = my_string_init_default();
		for (int i = 0; i < 4; i++)
			my_string_extraction(string, fp);
		fclose(fp);
		if (my_string_get_capacity(string) == 11) {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extract_has_proper_capacity\n"
				"my_string_get_capacity gave proper capacity\n", length);
			return SUCCESS;
		}
		else {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extract_has_proper_capacity\n"
				"my_string_get_capacity did not give proper capacity\n", length);
			return FAILURE;
		}
	}
}

Status test_jgaul_my_string_extract_has_proper_size(char* buffer, int length) {
	FILE* fp;
	fp = fopen("testing_in.txt", "r");
	if (!fp) {
		strncpy(buffer, "Failed to open file: testing_in.txt\n", length); return FAILURE;
	}
	else {
		MY_STRING string = my_string_init_default();
		for (int i = 0; i < 2; i++)
			my_string_extraction(string, fp);
		fclose(fp);
		if (my_string_get_size(string) == 3) {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extract_has_proper_size\n"
				"my_string_get_capacity gave proper size\n", length);
			return SUCCESS;
		}
		else {
			my_string_destroy(&string);
			strncpy(buffer, "test_jgaul_my_string_extract_has_proper_size\n"
				"my_string_get_capacity did not give proper size\n", length);
			return FAILURE;
		}
	}
}
Status test_jgaul_my_string_empty_on_empty_string(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("");

	if (my_string_empty(string)) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_empty_on_empty_string\n"
			"my_string_empty returned true for empty string\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_empty_on_empty_string\n"
			"my_string_empty returned false for empty string\n", length);
		return FAILURE;
	}
}
Status test_jgaul_my_string_empty_on_filled_string(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("not empty");

	if (!my_string_empty(string)) {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_empty_on_filled_string\n"
			"my_string_empty returned false for nonempty string\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		strncpy(buffer, "test_jgaul_my_string_empty_on_filled_string\n"
			"my_string_empty returned true for nonempty string\n", length);
		return FAILURE;
	}
}
Status test_jgaul_my_string_insertion_inerts_correctly(char* buffer, int length) {
	FILE* fp;
	char str[5];
	fp = fopen("testing_out.txt", "r+");
	if (!fp) {
		strncpy(buffer, "Failed to open file: testing_out.txt\n", length); return FAILURE;
	}
	else {
		MY_STRING string = my_string_init_c_string("Test");
		my_string_insertion(string, fp);
		fseek(fp, 0, SEEK_SET);
		MY_STRING string2;
		fgets(str, 5, fp);
		string2 = my_string_init_c_string(str);
		fclose(fp);
		if (my_string_compare(string, string2) == 0) {
			my_string_destroy(&string);
			my_string_destroy(&string2);
			strncpy(buffer, "test_jgaul_my_string_insertion_inerts_correctly\n"
				"my_string_insert correctly inserted string to file\n", length);
			return SUCCESS;
		}
		else {
			my_string_destroy(&string);
			my_string_destroy(&string2);
			strncpy(buffer, "test_jgaul_my_string_insertion_inerts_correctly\n"
				"my_string_insert incorrectly inserted string to file\n", length);
			return FAILURE;
		}
	}
}
Status test_jgaul_my_string_concat_has_correct_result(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("123");
	MY_STRING string2 = my_string_init_c_string("456");
	MY_STRING string3 = my_string_init_c_string("123456");
	my_string_concat(string, string2);
	if (my_string_compare(string, string3) == 0) {
		my_string_destroy(&string);
		my_string_destroy(&string2);
		my_string_destroy(&string3);
		strncpy(buffer, "test_jgaul_my_string_concat_has_correct_result\n"
			"my_string_concat correctly concatenated two strings\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		my_string_destroy(&string2);
		my_string_destroy(&string3);
		strncpy(buffer, "test_jgaul_my_string_concat_has_correct_result\n"
			"my_string_concat failed to concatenate two strings\n", length);
		return FAILURE;
	}
}
Status test_jgaul_my_string_concat_has_correct_status(char* buffer, int length) {
	MY_STRING string = my_string_init_c_string("123");
	MY_STRING string2 = my_string_init_c_string("456");

	if (my_string_concat(string, string2)) {
		my_string_destroy(&string);
		my_string_destroy(&string2);
		strncpy(buffer, "test_jgaul_my_string_concat_has_correct_status\n"
			"my_string_concat returned SUCCESS\n", length);
		return SUCCESS;
	}
	else {
		my_string_destroy(&string);
		my_string_destroy(&string2);
		strncpy(buffer, "test_jgaul_my_string_concat_has_correct_status\n"
			"my_string_concat returned FAILURE\n", length);
		return FAILURE;
	}
}

Status test_jgaul_my_string_insertion_invalid_file(char* buffer, int length) {
	MY_STRING hMy_string_1 = my_string_init_c_string("Computers");
	Status s = my_string_insertion(hMy_string_1, NULL);
	my_string_destroy(&hMy_string_1);
	
	if (!s) {
		strncpy(buffer, "test_jgaul_my_string_insertion_invalid_file\n"
			"my_string_insertion handled and invalid file pointer\n", length);
	}
	else {
		strncpy(buffer, "test_jgaul_my_string_insertion_invalid_file\n"
			"my_string_insertion incorrectly handled an invalid file pointer\n", length);
	}
	return !s;
}

Status test_jgaul_my_string_extraction_invalid_file(char* buffer, int length) {
	MY_STRING hMy_string_1 = my_string_init_c_string("Computers");
	Status s = my_string_extraction(hMy_string_1, NULL);
	my_string_destroy(&hMy_string_1);

	if (!s) {
		strncpy(buffer, "test_jgaul_my_string_extraction_invalid_file\n"
			"   \n", length);
	}
	else {
		strncpy(buffer, "test_jgaul_my_string_extraction_invalid_file\n"
			"   \n", length);
	}
	return !s;
}
