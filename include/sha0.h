#ifndef __CHASHLIB_SHA0_H__
#define __CHASHLIB_SHA0_H__

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    unsigned char buffer[64];
    uint64_t length;
    uint32_t a, b, c, d, e;
} CHashLib_sha0_ctx_t;

void CHashLib_SHA0_init(
    CHashLib_sha0_ctx_t *ctx
);

void CHashLib_SHA0_update(
    CHashLib_sha0_ctx_t *ctx,
    const unsigned char *data,
    size_t length
);

void CHashLib_SHA0_final(
    CHashLib_sha0_ctx_t *ctx,
    unsigned char output[20]
);

void CHashLib_SHA0_hash(
    const unsigned char *data,
    size_t length,
    unsigned char output[20]
);

#endif
