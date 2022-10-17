#include <stdio.h>
#include <strings.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "srandom.h"

char *gen(unsigned int len) {
	unsigned int i;
	char *pass;

	char *dict = "abcdefghijklmnopqrstuvwxyz" \
	             "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
	             "0123456789!@#$%^&*()-=+.,:;\"?";

	uint32_t dict_len = ((uint32_t)strlen(dict));

	/* allocating pass on memory. */
	pass = malloc(len * sizeof(char));

	/* generate random sequence. */
	for (i = 0; i < len; i++) {
		pass[i] = dict[urand_int(dict_len)];
	}

	return pass;
}

void print_logo() {
	printf(" _____ ___ ___\n");
	printf("|     | . | . |\n");
	printf("|_|_|_|  _|_  |\n");
	printf("      |_| |___|\n\n");
	printf("          ~0xbiel\n\n");
}

void usage(void) {
	fprintf(stderr, "usage: mpg [length]\n");
	fprintf(stderr, "where: [length] is the length of the desired password\n");
	fprintf(stderr, "       (greater than 5, lower than 4096).\n\n");
}

int main(int argc, char *argv[]) {
	unsigned int len;
	char *pass;

	/* determine if stdout is connected to a terminal */
	int tty = isatty(fileno(stdout));
	if (tty) {
		print_logo();
	}

	/* if there's no first argument, show help. */
	if (!argv[1]) {
		usage();
		exit(1);
	}

	/* get length argument and check it is within range */
	len = atoi(argv[1]);
	if (len > 4096 || len < 5) {
		usage();
		exit(1);
	}

	/* print message if tty */
	if (tty) {
		printf("here's your password: ");
	}

	pass = gen(len);
	printf("%s\n", pass);
	free(pass);

	return 0;
}
