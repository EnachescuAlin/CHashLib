#ifndef __CHASHLIB_MD5_H__
#define __CHASHLIB_MD5_H__

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    unsigned char buffer[64];
    uint64_t length;
    uint32_t a, b, c, d;
} CHashLib_md5_ctx_t;

void CHashLib_MD5_init(
    CHashLib_md5_ctx_t *ctx
);

void CHashLib_MD5_update(
    CHashLib_md5_ctx_t *ctx,
    const unsigned char *data,
    size_t length
);

void CHashLib_MD5_final(
    CHashLib_md5_ctx_t *ctx,
    unsigned char output[16]
);

void CHashLib_MD5_hash(
    const unsigned char *data,
    size_t length,
    unsigned char output[16]
);

#endif
