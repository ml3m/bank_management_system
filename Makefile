final:
	gcc -o Mlembank ./src/*.c -I./include -Wall -Werror -lcurl
clean:
	rm -rf Mlembank 
