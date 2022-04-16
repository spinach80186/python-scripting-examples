#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"


struct string {
	int size;
	int capacity;
	char* data;
};
typedef struct string String;


MY_STRING my_string_init_default(void) {
	String* str;
	str = (String*)malloc(sizeof(String));
	if (!str)
		return NULL;
	str->size = 0;
	str->capacity = 7;
	str->data = (char*)malloc(sizeof(char) * str->capacity);
	if (!str->data) {
		free(str); //Be sure to destroy the string instance if the data malloc fails
		return NULL;
	}
	return str;
}

void my_string_destroy(Item* pItem) {
	String* pMy_string = (String*)*pItem;
	free(pMy_string->data);
	free(pMy_string);
	*pItem = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string) {
	int strLength;
	int i;
	String* str;

	//set strLength to the number of non-null characters in the string
	for (strLength = 0; c_string[strLength] != '\0'; strLength++);

	str = (String*)malloc(sizeof(String));
	if (!str)
		return NULL;

	str->size = strLength;
	str->capacity = strLength + 1;

	str->data = (char*)malloc(sizeof(char) * str->capacity);
	if (!str->data) {
		free(str);
		return NULL;
	}
	for (i = 0; i < strLength; i++)
		str->data[i] = c_string[i];
	return str;
}

int my_string_get_capacity(MY_STRING hMy_string) {
	String* pMy_string = (String*)hMy_string;
	return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
	String* pMy_string = (String*)hMy_string;
	return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
	int i;
	int lSize = ((String*)hLeft_string)->size;
	int rSize = ((String*)hRight_string)->size;
	char* lData = ((String*)hLeft_string)->data;
	char* rData = ((String*)hRight_string)->data;

	//set i to the first index where a character differs between the two strings or a string ends
	for (i = 0; lData[i] == rData[i] && i < lSize - 1 && i < rSize - 1; i++);
	//see if both strings ended
	if (lSize == rSize)
		return lData[i] - rData[i];

	//Otherwise one string ended first
	if (i >= rSize - 1) //right str ended first, return first different char in left str minus 0
		return lData[i + 1];
	else            //otherwise the left str ended, return 0 minus the first different char in right str
		return -rData[i + 1];
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	int i;
	int noc;
	char ch;
	char* tmp;
	String* pMy_string = (String*)hMy_string;
	if (!fp)
		return FAILURE;

	noc = fscanf(fp, " %c", &ch);
	for (pMy_string->size = 0; noc == 1; pMy_string->size++) {
		if (isspace(ch)) {
			ungetc(ch, fp); //Prevents file pointer from progressing past whitespace
			break;
		}

		if (pMy_string->size >= pMy_string->capacity) {
			tmp = (char*)malloc(sizeof(char) * (pMy_string->capacity + 1));
			if (tmp == NULL) {
				return FAILURE;
			}
			for (i = 0; i < pMy_string->capacity; i++) {
				tmp[i] = pMy_string->data[i];
			}
			free(pMy_string->data);
			pMy_string->data = tmp;
			pMy_string->capacity++;
		}
		pMy_string->data[pMy_string->size] = ch;
		noc = fscanf(fp, "%c", &ch);
	}

	if (pMy_string->size == 0)
		return FAILURE;
	else
		return SUCCESS;
}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	if (!fp)
		return FAILURE;
	String* pMy_string = (String*)hMy_string;
	for (int i = 0; i < pMy_string->size; i++) {
		fprintf(fp, "%c", pMy_string->data[i]);
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	String* pMy_string = (String*)hMy_string;

	if (pMy_string->size >= pMy_string->capacity) {
		char* tmp;
		int i;
		tmp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
		if (!tmp)
			return FAILURE;
		for (i = 0; i < pMy_string->capacity; i++) {
			tmp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = tmp;
		pMy_string->capacity *= 2;
	}
	pMy_string->data[pMy_string->size++] = item;
	return SUCCESS;

}


Status my_string_pop_back(MY_STRING hMy_string) {
	String* pMy_string = (String*)hMy_string;
	if (pMy_string->size <= 0)
		return FAILURE;
	pMy_string->size--;
	return SUCCESS;

}

char* my_string_at(MY_STRING hMy_string, int index) {
	String* pMy_string = (String*)hMy_string;
	if (index < pMy_string->size && index >= 0) {
		return (pMy_string->data + index);
	}
	return NULL;
}

char* my_string_c_str(MY_STRING hMy_string) {
	String* pMy_string = (String*)hMy_string;

	if (pMy_string->size >= pMy_string->capacity) {
		char* tmp;
		int i;
		tmp = (char*)malloc(sizeof(char) * pMy_string->capacity + 1);
		if (!tmp)
			return FAILURE;
		for (i = 0; i < pMy_string->capacity; i++) {
			tmp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = tmp;
		pMy_string->capacity++;
	}
	pMy_string->data[pMy_string->size++] = '\0';
	return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	String* pResult = (String*)hResult;
	String* pAppend = (String*)hAppend;
	int size = pResult->size + pAppend->size;
	char* tmp;
	int i;
	if (size > pResult->capacity) {
		tmp = (char*)malloc(sizeof(char) * size);
		if (!tmp)
			return FAILURE;
		for (i = 0; i < pResult->size; i++) {
			tmp[i] = pResult->data[i];
		}
		free(pResult->data);
		pResult->data = tmp;
	}
	for (i = 0; i < pAppend->size; i++) {
		pResult->data[pResult->size + i] = pAppend->data[i];
	}
	pResult->size = size;
	return SUCCESS;
}


Boolean my_string_empty(MY_STRING hMy_string) {
	return (Boolean)((String*)hMy_string)->size == 0;
}

void my_string_assignment(Item* pLeft, Item Right) {
	String* pStrLeft = (String*)*pLeft;
	String* pStrRight = (String*)Right;

	if (pStrLeft == NULL) {
		pStrLeft = (String*)malloc(sizeof(String));
		if (pStrLeft == NULL)
			return;
		pStrLeft->size = 0; 
		pStrLeft->capacity = 0;
		pStrLeft->data = NULL;
	}

	if (pStrLeft->capacity < pStrRight->size) {
		char* tmp = (char*)malloc(sizeof(char) * pStrRight->size);
		if (pStrLeft->data)
			free(pStrLeft->data);
		if (!tmp) {
			pStrLeft->data = NULL;
			return;
		}
		pStrLeft->data = tmp;
		pStrLeft->capacity = pStrRight->size;
	}
	for (int i = 0; i < pStrRight->size; i++) {
		pStrLeft->data[i] = pStrRight->data[i];
	}
	pStrLeft->size = pStrRight->size;
	*pLeft = pStrLeft;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	
	int i;
	for (i = 0; i < my_string_get_size(word); i++)
	{
		if (*(my_string_at(word, i)) == guess)
			my_string_push_back(new_key, guess);
		else
			my_string_push_back(new_key, *(my_string_at(current_word_family, i)));
	}


	return SUCCESS;
}
