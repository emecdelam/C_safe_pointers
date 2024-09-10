make:
	@gcc -g -o safe_pointers.o safe_pointers.c

test:
	@gcc -g -o test_safe_pointers.o  test_safe_pointers.c
	./test_safe_pointers.o
	@rm test_safe_pointers.o

leak:
	@gcc -g -o test_safe_pointers.o  test_safe_pointers.c
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_safe_pointers.o 
	@rm test_safe_pointers.o
leaktemp:
	@gcc -g -o test_safe_pointers.o  temp.c
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_safe_pointers.o 
	@rm test_safe_pointers.o