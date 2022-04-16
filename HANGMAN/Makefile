CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = my_string.o main.o g_vector.o a_array.o

evil_hangman: $(OBJECTS)
	$(CC) $(CFLAGS) -o evil_hangman $(OBJECTS)
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
g_vector.o: g_vector.c g_vector.h generic.h
	$(CC) $(CFLAGS) -c g_vector.c -o g_vector.o
a_array.o: a_array.c a_array.h
	$(CC) $(CFLAGS) -c a_array.c -o a_array.o



unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
clean:
	rm string_driver $(OBJECTS) unit_test.o test_def.o evil_hangman
