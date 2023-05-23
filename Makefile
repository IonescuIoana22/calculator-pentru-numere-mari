build:
	gcc calculator.c -Wall -Werror -o calculator
run:
	./calculator
clean:
	rm calculator
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./calculator