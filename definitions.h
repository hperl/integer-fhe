/*
 *  definitions.h
 *  integer-fhe
 *
 *  Created by Henning Perl on 01.03.10.
 *
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define LAMBDA 4	// security parameter;		appropriate choice?
#define GAMMA 64		// bit-length of pk-ints;	appropriate choice? (NOTE: 128 crashes)
#define ETA 16		// bit-length of sk;		= LAMBDA^2
#define RHO 4		// bit-length of noise;		= LAMBDA
#define TAU 68		// # ints in pk;			= LAMBDA + GAMMA

#endif