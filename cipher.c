#include <stdio.h>
#include <stdint.h>

#include "badcipher.h"

int main(int argc, char **argv)
{
	uint16_t block[2] = {0xaabb, 0xccdd};
	uint16_t key[2] = {0x1122, 0x2233};

	uint16_t roundkeys[ROUNDS];
	badcipher_setup(roundkeys, key);


	badcipher_encrypt(block, roundkeys);
	printf("enc bk: %04x\n", block[0]);
	printf("enc bk: %04x\n", block[1]);

	badcipher_decrypt(block, roundkeys);
	printf("dec bk: %04x\n", block[0]);
	printf("dec bk: %04x\n", block[1]);
}
