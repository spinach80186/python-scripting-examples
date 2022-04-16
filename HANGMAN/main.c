#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "g_vector.h"
#include "a_array.h"
#include <ctype.h> 

void clearKeyboardBuffer();

int main(int argc, char* argv[]) {
	G_VECTOR dictionary[30];
	MY_STRING hMy_string = my_string_init_default();
	FILE* fp;
	Boolean playing = TRUE;

	//LOAD DICTIONARY INTO ARRAY OF VECTORS

	fp = fopen("dictionary.txt", "r");
	if (!fp) {
		printf("Failed to open dictionary!\n");
		exit(1);
	}
	for (int i = 0; i < 30; i++)
		dictionary[i] = g_vector_init_default(my_string_assignment, my_string_destroy);

	int size;
	Status reading = SUCCESS;
	while (1) {
		reading = my_string_extraction(hMy_string, fp);
		if (reading == FAILURE || hMy_string == NULL)
			break;
		size = my_string_get_size(hMy_string);
		g_vector_push_back(dictionary[size - 1], hMy_string);
	};
	fclose(fp);
	my_string_destroy(&hMy_string);


	while (playing) {
		A_ARRAY wordFamilies = NULL;
		G_VECTOR wordVector = g_vector_init_default(my_string_assignment, my_string_destroy);
		G_VECTOR tmpWordVector;

		MY_STRING key = NULL;
		MY_STRING newKey = NULL;
		MY_STRING word = NULL;
		MY_STRING guessedLetters = my_string_init_default();
		A_ARRAY maxNode = NULL;
		char guess;
		int word_size;
		int num_guesses;
		char answer;
		Boolean showWordCount = FALSE;

		while (1) {
			printf("What size word would you like to play with?\n");
			if (scanf(" %d", &word_size) == 1 && word_size < 30 && word_size > 1 && g_vector_get_size(dictionary[word_size - 1]) > 0) break;
			else printf("Please enter a number 2-29.\n");
			clearKeyboardBuffer();
		}
		clearKeyboardBuffer();
		while (1) {
			printf("How many guesses would you like to have?\n");
			if (scanf(" %d", &num_guesses) == 1 && num_guesses > 0) break;
			clearKeyboardBuffer();
		}
		clearKeyboardBuffer();
		while (1) {
			printf("Would you like to see how many words are left in the list? (y/n)\n");
			if (scanf(" %c", &answer) == 1 && (tolower(answer) == 'y')) {
				showWordCount = TRUE;
				break;
			}
			else if (tolower(answer) == 'n')
				break;
			clearKeyboardBuffer();
		}


		//load words of chosen length into the word vector
		for (int i = 0; i < g_vector_get_size(dictionary[word_size - 1]); i++)
			g_vector_push_back(wordVector, g_vector_at(dictionary[word_size - 1], i));

		newKey = my_string_init_default();
		key = my_string_init_default();
		for (int i = 0; i < word_size; i++) my_string_push_back(key, '-');

		while (num_guesses > 0) {

			printf("You have %d guesses left.\nUsed Letters: ", num_guesses);
			my_string_insertion(guessedLetters, stdout);
			printf("\nWord: ");
			my_string_insertion(key, stdout);
			printf("\nEnter Guess: ");

			while (1) {
				Boolean invalidLetter = FALSE;
				int ret = scanf(" %c", &guess);
				if (ret != 1) invalidLetter = TRUE;
				clearKeyboardBuffer();
				if (isalpha(guess)) {
					for (int i = 0; i < my_string_get_size(guessedLetters); i++) {
						if (*(my_string_at(guessedLetters, i)) == tolower(guess)) {
							invalidLetter = TRUE;
						}
					}
				}
				else invalidLetter = TRUE;
				if (!invalidLetter) break;
				else printf("Please guess a letter that you have not used yet.\n");
			}
			my_string_push_back(guessedLetters, tolower(guess));




			//generate avl tree with all the words in the word vector
			for (int i = 0; i < g_vector_get_size(wordVector); i++) {
				my_string_destroy(&newKey);
				newKey = my_string_init_default();
				word = g_vector_at(wordVector, i);           //get a word
				get_word_key_value(key, newKey, word, guess);//generate a nice little key to fit the word & guess
				a_array_insert(&wordFamilies, newKey, word); //add the word to its key family
			}

			//loop through the avl tree and print out the size of each index
			if (showWordCount) printTree(wordFamilies);

			//replace the current word vector with the one from the tree.

			maxNode = find_maximum_word_family(wordFamilies);
			if (showWordCount) printf("\nThe computer has %d possibilities remaining.\n\n", g_vector_get_size(a_array_get_index(maxNode)));
			if (my_string_compare(key, a_array_get_key(maxNode)) == 0) {
				printf("I'm sorry, there were no %c's in the word.\n", guess);
				num_guesses--;
			}
			my_string_destroy(&key);
			key = a_array_get_key(maxNode);
			a_array_unlink_key(maxNode);


			// Deep copy the chosen word vector
			tmpWordVector = g_vector_init_default(my_string_assignment, my_string_destroy);
			for (int i = 0; i < g_vector_get_size(a_array_get_index(maxNode)); i++) {
				my_string_assignment(&word, g_vector_at(a_array_get_index(maxNode), i));
				g_vector_push_back(tmpWordVector, word);
			}

			g_vector_destroy(&wordVector);
			wordVector = tmpWordVector;
			a_array_destroy(&wordFamilies);

			Boolean gameEnded = TRUE;
			for (int i = 0; i < my_string_get_size(key); i++) {
				if (*(my_string_at(key, i)) == '-') {
					gameEnded = FALSE;
				}
			}

			if (gameEnded) {
				printf("Congratulations! You guessed the word! (");
				my_string_insertion(key, stdout);
				printf(")\n");
			}

			if (num_guesses == 0) {
				printf("I'm sorry, the word I was thinking of was: ");
				my_string_insertion(g_vector_at(wordVector, rand() % (g_vector_get_size(wordVector))), stdout);
				printf("\n");
				gameEnded = TRUE;
			}
			if (gameEnded) {
				num_guesses = 0;
				while (1) {
					printf("Would you like to play again? (y/n)\n");
					if (scanf(" %c", &answer) == 1 && (tolower(answer) == 'y')) {
						playing = TRUE;
						break;
					}
					else if (tolower(answer) == 'n') {
						playing = FALSE;
						break;
					}
				}
			}

		}

		g_vector_destroy(&wordVector);
		my_string_destroy(&newKey);
		my_string_destroy(&key);
		my_string_destroy(&guessedLetters);
		

	}
	
	for (int i = 0; i < 30; i++) {
		g_vector_destroy(&dictionary[i]);
	}
	return 0;
}


void clearKeyboardBuffer() {
	int noc;
	char ch;
	do {
		noc = scanf("%c", &ch);
	} while (noc == 1 && ch != '\n' && ch != ' ' && ch != '\0');
}