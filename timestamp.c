/*
 * Linux: cc -g -Wall -O2 -o timestamp timestamp.c
 * QNX: qcc -g -Wc,-Wall -O2 -o timestamp timestamp.c
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/************************************************************* UINT64_MIN() ***/

static inline uint64_t uint64_min( uint64_t a, uint64_t b ) { return a > b ? b : a; }

/************************************************************** TIMESTAMP() ***/
/**
 * The function makes a timestamp in HH:mm:ss.ms format
 * and returns it in the provided buffer.
 *
 * \param buff the timestamp buffer
 * \param size buffer size
 *
 * return timestamp string length
 */
static int timestamp( char *buff, int size ) {
	struct timespec  ts;
	size_t           sz;

	clock_gettime( CLOCK_REALTIME, &ts );
	sz = strftime( buff, size, "%T", localtime( &ts.tv_sec ));

	if( size - sz > 4 ) {
		/*
		 * The following code compiles fine in 32 bit
		 * environment, but in 64 bit compiler gives
		 * different warnings depending on the optimization
		 * level (-O1, -O2, ...).
		 *
		 * sprintf( &buff[ sz ], ".%03d", ts.tv_nsec / 1000000 )
		 */
		sprintf( &buff[ sz ], ".%03ld", uint64_min( 999, ts.tv_nsec / 1000000 ));
		sz += 4;
	}

	return sz;
}

/******************************************************************* MAIN() ***/

int main() {
	struct timespec   ts;
	char              buff[ 100 ];

	clock_gettime( CLOCK_REALTIME, &ts );
	timestamp( buff, sizeof( buff ));
	printf( "%s\n", buff );

	return 0;
}

