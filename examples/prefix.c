#include<stdio.h>
#include<stdlib.h>

#include "perm.h"

int main() {
	struct perm_t* perm;
	uint8_t key[16] = { 0 };
	uint32_t out;
	int count = 0;

	FILE* fd = fopen("/dev/urandom", "r");
	fread(key, 1, 16, fd);
	fclose(fd);

	perm = perm_create(100, PERM_MODE_PREFIX, PERM_CIPHER_RC5, key, 16);
	if(perm == NULL) {
		fprintf(stderr, "Failed to create permutation! Error Code: %d\n",
				perm_get_last_error());
	}

	while(PERM_END != perm_next(perm, &out)) {
		fprintf(stdout, "%08u => %08u\n", count, out);
		count++;
	}

	perm_destroy(perm);

	return 0;
}
