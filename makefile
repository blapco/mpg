default:
	gcc mpg.c -o mpg
clean:
	rm mpg
install: 
	cp mpg /usr/bin/mpg
uninstall:
	rm /usr/bin/mpg
