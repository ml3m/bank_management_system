final:
	gcc -o login src/main.c src/bank.c src/cli.c src/iban_generator.c -I./include -Wall -Werror
clean:
	rm -rf main
