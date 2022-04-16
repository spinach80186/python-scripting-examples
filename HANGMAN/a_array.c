#include <stdlib.h>
#include "a_array.h"
#include "g_vector.h"
#include "my_string.h"
#ifdef max
#undef max
#endif

struct node;
typedef struct node Node;
struct node {
	int height;
	Node* left;
	Node* right;

	MY_STRING key;
	G_VECTOR index;
};

int height(Node* node) {
	return node ? node->height : 0;
}

int max(int a, int b) {
	return ((a) > (b) ? (a) : (b));
}

Node* rotateLeft(Node* node) {
	Node* rightChild = node->right;
	Node* rightChildLeftLeaf = rightChild->left;
	rightChild->left = node;
	node->right = rightChildLeftLeaf;

	node->height = max(height(node->left), height(node->right)) + 1;
	rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
	return rightChild;
}
Node* rotateRight(Node* node) {
	Node* leftChild = node->left;
	Node* leftChildRightLeaf = leftChild->right;
	leftChild->right = node;
	node->left = leftChildRightLeaf;

	node->height = max(height(node->left), height(node->right)) + 1;
	leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
	return leftChild;
}

Status a_array_insert(A_ARRAY* hWordFamilies, MY_STRING newKey, MY_STRING word) {
	//avl tree is made of (key, pointer) pairs
	Node** wordFamilies = (Node**)hWordFamilies;
	int i = 0;
	int comparison;
	int balance;

	if (*wordFamilies == NULL)
	{
		Node* newRoot = (Node*)malloc(sizeof(Node));
		if (newRoot == NULL) return FAILURE;

		newRoot->left = NULL;
		newRoot->right = NULL;
		newRoot->height = 0;
		newRoot->key = my_string_init_default();
		newRoot->index = g_vector_init_default(my_string_assignment, my_string_destroy);

		for (i = 0; i < my_string_get_size(newKey); i++)
			my_string_push_back(newRoot->key, *my_string_at(newKey, i));

		g_vector_push_back(newRoot->index, word); //avl tree is full of pointers

		*wordFamilies = newRoot;

		return SUCCESS;
	}

	comparison = my_string_compare(newKey, (*wordFamilies)->key);
	if (comparison < 0) {
		if (a_array_insert((A_ARRAY) &((*wordFamilies)->left), newKey, word) == FAILURE) return FAILURE;
	}
	else if (comparison > 0) {
		if (a_array_insert((A_ARRAY) &((*wordFamilies)->right), newKey, word) == FAILURE) return FAILURE;
	}
	else {
		g_vector_push_back((*wordFamilies)->index, word);
	}

	(*wordFamilies)->height = max(height((*wordFamilies)->left), height((*wordFamilies)->right)) + 1;

	balance = height((*wordFamilies)->left) - height((*wordFamilies)->right);
	if (balance > 1) {
		// Left Heavy Trees
		if (height((*wordFamilies)->left->left) < height((*wordFamilies)->left->right)) {
			(*wordFamilies)->left = rotateLeft((*wordFamilies)->left);
		}
		(*wordFamilies) = rotateRight(*wordFamilies);
		return SUCCESS;
	}
	else if (balance < -1) {
		// Right Heavy Trees
		if (height((*wordFamilies)->right->left) > height((*wordFamilies)->right->right)) {
			(*wordFamilies)->right = rotateRight((*wordFamilies)->right);
		}
		(*wordFamilies) = rotateLeft(*wordFamilies);
		return SUCCESS;
	}
	return SUCCESS;
}



G_VECTOR a_array_get_index(A_ARRAY a_array) {
	return ((Node*)a_array)->index;
}

MY_STRING a_array_get_key(A_ARRAY a_array) {
	return ((Node*)a_array)->key;
}

void a_array_unlink_key(A_ARRAY a_array) {
	((Node*)a_array)->key = NULL;
}


void a_array_unlink_node_index(A_ARRAY node) {
	Node* temp = (Node*)node;
	temp->index = NULL;
}


A_ARRAY find_maximum_word_family(A_ARRAY root) {
	A_ARRAY maxNode = (Node*)root;

	if (((Node*)root)->left) {
		A_ARRAY leftChild = find_maximum_word_family(((Node*)root)->left);
		maxNode = g_vector_get_size(a_array_get_index(maxNode)) > g_vector_get_size(a_array_get_index(leftChild)) ? maxNode : leftChild;
	}
	if (((Node*)root)->right) {
		A_ARRAY rightChild = find_maximum_word_family(((Node*)root)->right);
		maxNode = g_vector_get_size(a_array_get_index(maxNode)) > g_vector_get_size(a_array_get_index(rightChild)) ? maxNode : rightChild;
	}
	return maxNode;
}

void a_array_destroy(A_ARRAY* a_array) {
	Node* root = *a_array;
	if (root != NULL) {
		if (root->index != NULL) g_vector_destroy(&root->index);
		a_array_destroy((A_ARRAY*) &(root->left));
		a_array_destroy((A_ARRAY*) &(root->right));
		if (root->key) my_string_destroy(&root->key);
		free(root);
	}
	*a_array = NULL;
}

void printTree(A_ARRAY root) {
	Node* pRoot = (Node*)root;
	if (root == NULL) return;
	my_string_insertion(pRoot->key, stdout);
	printf(" %d\n", g_vector_get_size(pRoot->index));
	printTree((A_ARRAY) pRoot->left);
	printTree((A_ARRAY) pRoot->right);
}