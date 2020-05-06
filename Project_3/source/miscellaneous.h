/*
 * miscellaneous.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Disha
 */

#ifndef MISCELLANEOUS_H_
#define MISCELLANEOUS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

char *dec_to_bstr(uint8_t x, uint8_t size);

void gen_pattern(uint8_t n, uint8_t s, uint8_t *buffer);

#endif /* MISCELLANEOUS_H_ */
