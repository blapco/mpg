#include <stdio.h>
#include <strings.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "srandom.h"

char* gen(unsigned int len) {
	unsigned int random;
	unsigned int ilatin, iulatin, iansi;
	unsigned int i;
	char *pass;

	char *dict = "abcdefghijklmnopqrstuvwxyz" \
	             "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
	             "0123456789!@#$%^&*()-=+.,:;\"?";

	uint32_t dict_len = ((uint32_t)strlen(dict));

	/* allocating pass on memory. */
	pass = (char *)malloc(len * sizeof(char));

	/* generate random sequence. */
	for (i = 0; i < len; i++) {
		pass[i] = dict[urand_int(dict_len)];
	}

	return pass;
}

void printLogo() {
	printf(" _____ ___ ___\n");
	printf("|     | . | . |\n");
	printf("|_|_|_|  _|_  |\n");
	printf("      |_| |___|\n\n");
	printf("          ~0xbiel\n\n");
}

int main(int argc, char **argv[]) {
	unsigned int len;
	char *pass;

	/* determine if stdout is connected to a terminal */
	int tty = isatty(fileno(stdout));

	/* if there's no first argument, show help. */

	if (!argv[1]) {
		if(tty) {
			printLogo();
			printf("usage: mpg [password length]\n\n");
		}
		exit(1);
	}
	else if (atoi(argv[1]) > 4096 || atoi(argv[1]) < 5) {
		if (tty) {
			printLogo();
			printf("the length must be higher than 5 and lower than 4096.\n");
		}
		exit(1);
	}
	else {
		len = atoi(argv[1]);
	}

	if (tty) {
		printLogo();
		printf("here's your password: ");
	}

	pass = gen(len);
	printf("%s\n", pass);
	free(pass);

	free(pass);

	return 0;
}
