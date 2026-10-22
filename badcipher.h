#pragma once
#ifndef _BADCIPHER
#define _BADCIPHER
#include <stdint.h>

#define ROUNDS 8
#define SWAP(a, b) { uint16_t x = a; a = b; b = x; }

// we don't need bit rotation where we're going. we're rockin' an AX cipher here HAHA
#define ROUND(x, y, k) (x ^= k, x += y)
#define DROUND(x, y, k) (x -= y, x ^= k)

static void badcipher_setup(uint16_t roundkeys[ROUNDS], uint16_t key[2])
{
	uint16_t a = key[0];
	uint16_t b = key[1];

	for(int i = 0; i < ROUNDS; i++)
	{
		roundkeys[i] = a;
		ROUND(a, b, i);
	}
}

static void badcipher_encrypt(uint16_t block[2], uint16_t roundkeys[ROUNDS])
{
	for(int i = 0; i < ROUNDS; i++)
	{
		ROUND(block[0], block[1], roundkeys[i]);
		SWAP(block[0], block[1]);
	}
}

static void badcipher_decrypt(uint16_t block[2], uint16_t roundkeys[ROUNDS])
{
	for(int i = ROUNDS - 1; i >= 0; i--)
	{
		SWAP(block[1], block[0]);
		DROUND(block[0], block[1], roundkeys[i]);
	}
}

#endif