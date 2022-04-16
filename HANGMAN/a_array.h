#pragma once
#include "generic.h"
#include "g_vector.h"
#include "my_string.h"

typedef void* A_ARRAY;

Status a_array_insert(A_ARRAY* hWordFamilies, MY_STRING newKey, MY_STRING word);
A_ARRAY find_maximum_word_family(A_ARRAY root);
G_VECTOR a_array_get_index(A_ARRAY a_array);
MY_STRING a_array_get_key(A_ARRAY a_array);
void a_array_unlink_key(A_ARRAY a_array);
void a_array_destroy(A_ARRAY* a_array);
void a_array_unlink_node_index(A_ARRAY node);

void printTree(A_ARRAY root);