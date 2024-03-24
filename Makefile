final:
	gcc -o main src/main.c src/bank.c src/cli.c src/iban_generator.c -I./include -Wall -Werror 
