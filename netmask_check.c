/*
 * QNX: qcc -g -Wc,-Wall -l socket -o netmask_check netmask_check.c
 * Ubuntu: cc -Wall -g -l socket -o netmask_check netmask_check.c
 */
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

/************************************************************* CHECK_MASK() ***/
/*
 * The function checks whether a netmask is valid.
 *
 * \param mask the mask in a dot format
 *
 * \return 0 - mask valid, -1 - mask invalid
 */
static int check_mask( char *mask ) {
	struct in_addr   netmask;
	uint32_t         maskl;
	int              i, maskbits;

	/*
	 * If the netmask has a dot, assume it is
	 * the netmask as an ip address
	 */
	if( strchr( mask, '.' )) {
		if( ! inet_aton( mask, &netmask )) {
			return -1;
		}

		/* Calculate the number of network bits */
		maskl = ntohl( netmask.s_addr );

		/* Handle special cases */
		if( 0 == maskl || INADDR_NONE == maskl ) {
			return -1;
		}

		for( maskbits = 32;
			( maskl & ( 1L << ( 32 - maskbits ))) == 0;
			maskbits-- )
			;

		/* Re-create the netmask and compare to the origianl
		 * to make sure it is a valid netmask.
		 */
		mask = 0;

		for( i = 0; i < maskbits; i++ )
			maskl |= 1 << ( 31 - i );

		if( maskl != ntohl( netmask.s_addr )) {
			return -1;
		}
	}

	return 0;
}

/******************************************************************* MAIN() ***/

int main( int argc, char *argv[] ) {
	if( 0 == check_mask( argv[ 1 ] ))
		printf( "The mask is valid\n" );
	else
		printf( "The mask is not valid\n" );

	return 0;
}

