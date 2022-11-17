#include <stdint.h>
#include <sys/random.h>

#include "srandom.h"

uint32_t urand_int(uint32_t limit) {
#if defined(__OpenBSD__) || defined(__APPLE__)
	/**
	 * On apple and openbsd, arc4random(), a cryptographically secure random
	 * number generation function can be used.
	 */
	return arc4random() % limit;
#else 
	/**
	 * On linux use getrandom() which uses /dev/urandom.
	 */
	uint32_t val;
	getrandom(&val, sizeof(val), 0);
	return val % limit;
#endif /* __OpenBSD__ || __APPLE__ */
}

