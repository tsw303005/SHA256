#ifndef SHA256_H
#define SHA256_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef struct {
    BYTE data[64];
    WORD result[8];
    unsigned long long datalen;
    unsigned long long bitlen;
} SHA256_CTX;


// define sha256 process function
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE **data, size_t len);
void sha256_final(SHA256_CTX *ctx, BYTE *hash_result);
void sha256_show_result(BYTE *hash_result);

#endif