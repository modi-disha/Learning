/*
 * miscellaneous.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#include "miscellaneous.h"
/**
 * Convert decimal number into absolute binary number by performing shift and bit-mask
 * operation, convert the output numbers in character values and add two addition
 * '0b' in start of the string to satisfy binary format
 */
char *dec_to_bstr(uint8_t x, uint8_t size)
{
	int n = 0, ptr = 2;
	char *binary_str = (char *)calloc(10, sizeof(char));
	if(!binary_str)
	{
		printf("NULL Pointer!\n");
		exit(0);
	}
	*(binary_str + 0) = '0';
	*(binary_str + 1) = 'b';

	for (int i = size - 1; i >= 0; i--, ptr++)
	{
		n = x >> i;
		*(binary_str + ptr) = ((n & 1) == 1) ? '1' : '0';
	}
	*(binary_str + ptr) = '\0';
	return binary_str;
}

