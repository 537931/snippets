#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**************************************************************** COMPARE() ***/
/**
 * This function compares two floating point numbers. It is called
 * by qsort().
 *
 * \param[in] v1 pointer to the first number
 * \param[in] v2 pointer to the second number
 *
 * \return  1 if first number is greater than second
 *         -1 if second number is greater than first
 *          0 if the numbers are equal
 *
 * \see qsort
 */
static int compare( const void *v1, const void *v2 ) {
	double	f1 = *(double *) v1;
	double	f2 = *(double *) v2;

	if( f1 > f2 )
		return 1;

	if( f1 < f2 )
		return -1;

	return 0;
}

/********************************************************** MEDIAN_FILTER() ***/
/**
 * This function implements a median filter. The data is filtered in
 * the same place. If you want to keep original data back it up before
 * calling this function.
 *
 * \param[in|out] data array of points for filtering
 * \param[in] size size of the array
 * \param[in] width filter window width
 */
static int median_filter( double *data, size_t size, int width ) {
	double		*window;
	int			i, j, k;

	if( NULL == ( window = (double *) alloca( width * sizeof( double )))) {
		printf( "%s: %d: alloca(): %d", __FILE__, __LINE__, errno );
		return -1;
	}

	for( i = 0; i < size; i++ ) {
		for( j = 0; j < width; j++ ) {
			k = i + j - width / 2;
		
			if( k < 0 )
				k = -k - 1;

			if( k >= size )
				k = size - ( k - size ) - 1;

			window[ j ] = data[ k ];
		}

		qsort( window, width, sizeof( double ), compare );
		data[ i ] = window[ width / 2 ];

//#define __PRINT_FILTER_STEPS__
#ifdef __PRINT_FILTER_STEPS__
		printf( "%d, %.3f, ", i, data[ i ] );

		for( j = 0; j < width; j++ )
			printf( "%.3f, ", window[ j ] );

		printf( "\n" );
#endif /* __PRINT_FILTER_STEPS__ */
	}

	return 0;
}

#define __TEST_FILTER__
#ifdef __TEST_FILTER__
/******************************************************************* MAIN() ***/

int main() {
//	double	data[] = {
//		2.092, 2.115, 2.101, 2.101, 2.101, 2.099, 2.098,
//		2.097, 2.097, 2.096, 2.096, 2.097, 2.096, 2.095,
//		2.095, 2.094, 2.093, 2.093, 2.092, 2.093, 2.093,
//		2.095, 2.097, 2.098, 2.098, 2.099, 2.099, 2.099,
//		2.100, 2.100, 2.099, 2.100, 2.099
//	};
	double data[] = {
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 800, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817,
		605, 605, 607, 606, 608, 605, 605, 606, 608, 604,
		817, 818, 818, 816, 818, 815, 815, 814, 816, 817 };

	const size_t  nitems = sizeof( data ) / sizeof( data[ 0 ] );
	int		      i;

	for( i = 0; i < nitems; i++ )
		printf( "%4.3f, ", data[ i ] );

	printf( "\n" );

	if( 0 == median_filter( data, nitems, 19 )) {
		for( i = 0; i < nitems; i++ )
			printf( "%4.3f, ", data[ i ] );
	}

	printf( "\n" );
	return 0;
}
#endif /* __TEST_FILTER__ */
