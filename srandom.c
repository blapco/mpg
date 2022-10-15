#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "srandom.h"

/**
 * Get a random uint32_t from /dev/urandom.
 * This is very roughly based on how OpenBSD's arc4random() uses its
 * keystream to generate a random uint32, but instead of a ChaCha20-based
 * keystream we just use raw data from /dev/urandom.
 */
void get_urandom(uint32_t *val) {
	int urand = open("/dev/urandom", O_RDONLY);
	if (urand == -1) {
		printf("panic: could not open /dev/urandom.\n");
		exit(1);
	}

	unsigned char *ks = malloc(sizeof(*val));
	memset(ks, 0, sizeof(*val));

	// fill keystream with sizeof(*val) random data from /dev/urandom
	size_t result = read(urand, ks, sizeof(*val));
 	if (result != sizeof(*val)) {
		printf("panic: read incorrect amount of data.\n");
		exit(1);
	}
	close(urand);

	// copy random data into val
	memcpy(val, ks, sizeof(*val));

	// zero out the keystream and free it since we don't need it anymore
	memset(ks, 0, sizeof(*val));
	free(ks);
}

uint32_t urand_int(uint32_t limit) {
#if defined(__OpenBSD__) || defined(__APPLE__)
	/**
	 * On apple and openbsd, arc4random(), a cryptographically secure random
	 * number generation function can be used.
	 */
	return arc4random() % limit;
#else 
	/**
	 * On linux and everything else we need to use /dev/urandom to generate
	 * cryptographically secure pseudorandom numbers. This is a little more
	 * involved than macos/openbsd (see: get_urandom() above).
	 */
	uint32_t val;
	get_urandom(&val);
	return val % limit;
#endif /* __OpenBSD__ || __APPLE__ */
}

