#ifndef __CHASHLIB_MD2_H__
#define __CHASHLIB_MD2_H__

#include <stdint.h>

typedef struct
{
    unsigned char state[16];
    unsigned char checksum[16];
    unsigned char buffer[16];
    uint32_t length;
} CHashLib_md2_ctx_t;

void CHashLib_MD2_init(
    CHashLib_md2_ctx_t *ctx
);

void CHashLib_MD2_update(
    CHashLib_md2_ctx_t *ctx,
    const unsigned char *data,
    uint32_t length
);

void CHashLib_MD2_final(
    CHashLib_md2_ctx_t *ctx,
    unsigned char output[16]
);

void CHashLib_MD2_hash(
    const unsigned char *data,
    uint32_t length,
    unsigned char output[16]
);

#endif
