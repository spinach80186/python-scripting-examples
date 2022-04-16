#pragma once
#include "generic.h"

struct g_vector {
	int size;
	int capacity;
	Item_ptr data;
	void (*item_assign)(Item_ptr phLeft, Item hRight);
	void (*item_destroy)(Item_ptr phLeft);
};
typedef struct g_vector G_Vector;

typedef G_Vector* G_VECTOR;
G_VECTOR g_vector_init_default(void (*item_assign)(Item*, Item), void (*item_destroy)(Item*));
int g_vector_get_size(G_VECTOR hG_Vector);
int g_vector_get_capacity(G_VECTOR hG_Vector);

Status g_vector_push_back(G_VECTOR hG_Vector, Item item);
Status g_vector_pop_back(G_VECTOR hG_Vector);
Item g_vector_at(G_VECTOR hG_Vector, int index);

void g_vector_destroy(G_VECTOR* phG_Vector);
