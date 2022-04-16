#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_jgaul_test_my_string_compare_prefix_word(char* buffer, int length);
Status test_jgaul_test_my_string_compare_identical_word(char* buffer, int length);
Status test_jgaul_test_my_string_compare_same_size_words(char* buffer, int length);
Status test_jgaul_test_my_string_test_get_size(char* buffer, int length);
Status test_jgaul_test_my_string_test_get_capacity(char* buffer, int length);
Status test_jgaul_my_string_destroy_sets_handle_NULL(char* buffer, int length);
Status test_jgaul_init_string_default_has_capacity_7(char* buffer, int length);
Status test_jgaul_pop_back_increments_string_size(char* buffer, int length);
Status test_jgaul_pop_back_handles_empty_string(char* buffer, int length);
Status test_jgaul_my_string_at_returns_correct_char(char* buffer, int length);
Status test_jgaul_my_string_at_handles_negative_index(char* buffer, int length);
Status test_jgaul_my_string_at_handles_index_too_large(char* buffer, int length);
Status test_jgaul_my_string_init_c_string_has_correct_size(char* buffer, int length);
Status test_jgaul_my_string_extraction_gets_word_correctly(char* buffer, int length);
Status test_jgaul_my_string_extract_has_proper_capacity(char* buffer, int length);
Status test_jgaul_my_string_extract_has_proper_size(char* buffer, int length);
Status test_jgaul_my_string_empty_on_empty_string(char* buffer, int length);
Status test_jgaul_my_string_empty_on_filled_string(char* buffer, int length);
Status test_jgaul_my_string_insertion_inerts_correctly(char* buffer, int length);
Status test_jgaul_my_string_concat_has_correct_result(char* buffer, int length);
Status test_jgaul_my_string_concat_has_correct_status(char* buffer, int length);
Status test_jgaul_my_string_insertion_invalid_file(char* buffer, int length);
Status test_jgaul_my_string_extraction_invalid_file(char* buffer, int length);
#endif

