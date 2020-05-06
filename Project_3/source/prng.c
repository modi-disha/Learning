/*
 * prng.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

/* @Ref: https://www.geeksforgeeks.org/pseudo-random-number-generator-prng */
/*	Conventional pseudo random number generator:
	 Xn+1 = (aXn + c) mod m
	 where X is the sequence of pseudo-random values
	 m, 0 < m  - modulus
	 a, 0 < a < m  - multiplier
	 c, 0 ≤ c < m  - increment
	 x0, 0 ≤ x0 < m  - the seed or start value
 */
#include "miscellaneous.h"

void gen_pattern(uint8_t n, uint8_t s, uint8_t *buffer)
{
	uint8_t x[n + 1];
	x[0] = s;

	for(uint8_t i = 0; i < n; i++)
	{
		x[i + 1] = (13 * x[i] + 111) % 255;
		*(buffer + i) = x[i + 1];
	}
}
