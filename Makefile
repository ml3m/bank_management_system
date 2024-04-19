final:
	gcc -o login ./src/*.c -I./include -Wall -Werror -lcurl
clean:
	rm -rf login
