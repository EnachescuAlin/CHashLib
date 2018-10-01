#ifndef __CHASHLIB_MD4_H__
#define __CHASHLIB_MD4_H__

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    unsigned char buffer[64];
    uint64_t length;
    uint32_t a, b, c, d;
} CHashLib_md4_ctx_t;

void CHashLib_MD4_init(
    CHashLib_md4_ctx_t *ctx
);

void CHashLib_MD4_update(
    CHashLib_md4_ctx_t *ctx,
    const unsigned char *data,
    size_t length
);

void CHashLib_MD4_final(
    CHashLib_md4_ctx_t *ctx,
    unsigned char output[16]
);

void CHashLib_MD4_hash(
    const unsigned char *data,
    size_t length,
    unsigned char output[16]
);

#endif
