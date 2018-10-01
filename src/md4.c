#include "md4.h"
#include "utils.h"

#include <string.h>

#define F0(x, y, z) ((x & y) | ((~x) & z))
#define F1(x, y, z) ((x & y) | (x & z) | (y & z))
#define F2(x, y, z) (x ^ y ^ z)

#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)))

#define R0(a, b, c, d, i, s, buf)                               \
    a += F0(b, c, d) + buf[i];                                  \
    a = LEFT_ROTATE(a, s)

#define R1(a, b, c, d, i, s, buf)                               \
    a += F1(b, c, d) + buf[i] + ((uint32_t) 0x5a827999);        \
    a = LEFT_ROTATE(a, s)

#define R2(a, b, c, d, i, s, buf)                               \
    a += F2(b, c, d) + buf[i] + ((uint32_t) 0x6ed9eba1);        \
    a = LEFT_ROTATE(a, s)

static void CHashLib_MD4_process_chunk(CHashLib_md4_ctx_t *ctx)
{
    uint32_t tmp_a = ctx->a;
    uint32_t tmp_b = ctx->b;
    uint32_t tmp_c = ctx->c;
    uint32_t tmp_d = ctx->d;

    uint32_t *buffer = (uint32_t*) ctx->buffer;

    R0(tmp_a, tmp_b, tmp_c, tmp_d,  0,  3, buffer);
    R0(tmp_d, tmp_a, tmp_b, tmp_c,  1,  7, buffer);
    R0(tmp_c, tmp_d, tmp_a, tmp_b,  2, 11, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_a,  3, 19, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d,  4,  3, buffer);
    R0(tmp_d, tmp_a, tmp_b, tmp_c,  5,  7, buffer);
    R0(tmp_c, tmp_d, tmp_a, tmp_b,  6, 11, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_a,  7, 19, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d,  8,  3, buffer);
    R0(tmp_d, tmp_a, tmp_b, tmp_c,  9,  7, buffer);
    R0(tmp_c, tmp_d, tmp_a, tmp_b, 10, 11, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_a, 11, 19, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, 12,  3, buffer);
    R0(tmp_d, tmp_a, tmp_b, tmp_c, 13,  7, buffer);
    R0(tmp_c, tmp_d, tmp_a, tmp_b, 14, 11, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_a, 15, 19, buffer);

    R1(tmp_a, tmp_b, tmp_c, tmp_d,  0,  3, buffer);
    R1(tmp_d, tmp_a, tmp_b, tmp_c,  4,  5, buffer);
    R1(tmp_c, tmp_d, tmp_a, tmp_b,  8,  9, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_a, 12, 13, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d,  1,  3, buffer);
    R1(tmp_d, tmp_a, tmp_b, tmp_c,  5,  5, buffer);
    R1(tmp_c, tmp_d, tmp_a, tmp_b,  9,  9, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_a, 13, 13, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d,  2,  3, buffer);
    R1(tmp_d, tmp_a, tmp_b, tmp_c,  6,  5, buffer);
    R1(tmp_c, tmp_d, tmp_a, tmp_b, 10,  9, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_a, 14, 13, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d,  3,  3, buffer);
    R1(tmp_d, tmp_a, tmp_b, tmp_c,  7,  5, buffer);
    R1(tmp_c, tmp_d, tmp_a, tmp_b, 11,  9, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_a, 15, 13, buffer);

    R2(tmp_a, tmp_b, tmp_c, tmp_d,  0,  3, buffer);
    R2(tmp_d, tmp_a, tmp_b, tmp_c,  8,  9, buffer);
    R2(tmp_c, tmp_d, tmp_a, tmp_b,  4, 11, buffer);
    R2(tmp_b, tmp_c, tmp_d, tmp_a, 12, 15, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d,  2,  3, buffer);
    R2(tmp_d, tmp_a, tmp_b, tmp_c, 10,  9, buffer);
    R2(tmp_c, tmp_d, tmp_a, tmp_b,  6, 11, buffer);
    R2(tmp_b, tmp_c, tmp_d, tmp_a, 14, 15, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d,  1,  3, buffer);
    R2(tmp_d, tmp_a, tmp_b, tmp_c,  9,  9, buffer);
    R2(tmp_c, tmp_d, tmp_a, tmp_b,  5, 11, buffer);
    R2(tmp_b, tmp_c, tmp_d, tmp_a, 13, 15, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d,  3,  3, buffer);
    R2(tmp_d, tmp_a, tmp_b, tmp_c, 11,  9, buffer);
    R2(tmp_c, tmp_d, tmp_a, tmp_b,  7, 11, buffer);
    R2(tmp_b, tmp_c, tmp_d, tmp_a, 15, 15, buffer);

    ctx->a += tmp_a;
    ctx->b += tmp_b;
    ctx->c += tmp_c;
    ctx->d += tmp_d;
}

void CHashLib_MD4_init(CHashLib_md4_ctx_t *ctx)
{
    memset(ctx->buffer, 0, 64);
    ctx->length = 0;

    ctx->a = 0x67452301;
    ctx->b = 0xefcdab89;
    ctx->c = 0x98badcfe;
    ctx->d = 0x10325476;
}

void CHashLib_MD4_update(CHashLib_md4_ctx_t *ctx, const unsigned char *data, size_t length)
{
    while (length > 0) {
        uint32_t currentPos = ctx->length & 63;
        uint32_t diff = 64 - currentPos;
        if (diff <= length) {
            memcpy(ctx->buffer + currentPos, data, diff);
            ctx->length += diff;
            length -= diff;
            data += diff;

            CHashLib_MD4_process_chunk(ctx);
        } else {
            memcpy(ctx->buffer + currentPos, data, length);
            ctx->length += length;
            return;
        }
    }
}

void CHashLib_MD4_final(CHashLib_md4_ctx_t *ctx, unsigned char output[16])
{
    // prepare original length in bits
    unsigned char bitsArray[8];
    uint64_t bits = ctx->length << 3;
    CHashLib_encode_uint32((uint32_t) (bits >>  0), bitsArray + 0);
    CHashLib_encode_uint32((uint32_t) (bits >> 32), bitsArray + 4);

    // append padding
    uint32_t currentPos = ctx->length & 63;
    CHashLib_MD4_update(ctx, CHashLib_padding,
        currentPos < 56 ? (56 - currentPos) : (120 - currentPos));

    // append original length in bits
    CHashLib_MD4_update(ctx, bitsArray, 8);

    // store the hash in hex
    CHashLib_encode_uint32(ctx->a, output +  0);
    CHashLib_encode_uint32(ctx->b, output +  4);
    CHashLib_encode_uint32(ctx->c, output +  8);
    CHashLib_encode_uint32(ctx->d, output + 12);
}

void CHashLib_MD4_hash(const unsigned char *data, size_t length, unsigned char output[16])
{
    CHashLib_md4_ctx_t ctx;

    CHashLib_MD4_init(&ctx);
    CHashLib_MD4_update(&ctx, data, length);
    CHashLib_MD4_final(&ctx, output);
}
