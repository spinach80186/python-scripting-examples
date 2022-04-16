#include "g_vector.h"
#include <stdio.h>
#include <stdlib.h>



G_VECTOR g_vector_init_default(void (*item_assign)(Item_ptr, Item),
	void (*item_destroy)(Item_ptr)) {
	G_Vector* pVector = NULL;
	pVector = (G_Vector*)malloc(sizeof(G_Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 2;
		pVector->item_assign = item_assign;
		pVector->item_destroy = item_destroy;
		pVector->data = (Item_ptr)malloc(sizeof(void*) * pVector->capacity);
		if (pVector->data == NULL) {
			free(pVector);
			pVector = NULL;
		}
		else {
			for (int i = 0; i < pVector->capacity; ++i)
				pVector->data[i] = NULL;
		}
	}
	return pVector;
}
int g_vector_get_size(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->size;
}
int g_vector_get_capacity(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->capacity;
}

Status g_vector_push_back(G_VECTOR hG_Vector, Item item) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	Item_ptr temp;
	int i;
	if (pVector->size >= pVector->capacity) {
		temp = (Item_ptr)malloc(sizeof(Item) * pVector->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pVector->capacity; ++i)
			temp[i] = pVector->data[i];
		pVector->capacity *= 2;
		for (i = pVector->size; i < pVector->capacity; ++i)
			temp[i] = NULL;
		free(pVector->data);
		pVector->data = temp;
	}
	pVector->item_assign(&pVector->data[pVector->size], item);
	pVector->size++;
	return SUCCESS;
}
Status g_vector_pop_back(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (pVector->size <= 0)
		return FAILURE;
	pVector->size--;
	return SUCCESS;


}
Item g_vector_at(G_VECTOR hG_Vector, int index) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (index<0 || index>pVector->size) {
		return NULL;
	}
	return pVector->data[index];
}

void g_vector_destroy(G_VECTOR* phG_Vector) {
	G_Vector* pVector = (G_Vector*)*phG_Vector;
	int i;
	for (i = 0; i < pVector->capacity;++i) {
		if (pVector->data[i] != NULL)
			pVector->item_destroy(&pVector->data[i]);
	}
	free(pVector->data);
	free(pVector);
	*phG_Vector = NULL;
}