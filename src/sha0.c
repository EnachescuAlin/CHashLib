#include "sha0.h"
#include "utils.h"

#include <string.h>
#include <stdio.h>

//#define F0(b, c, d) ((b & c) | ((~b) & d))
#define F0(B, C, D) ((((C) ^ (D)) & (B)) ^ (D))
#define F1(b, c, d) (b ^ c ^ d)
#define F2(b, c, d) ((b & c) | (b & d) | (d & c))
#define F3(b, c, d) (b ^ c ^ d)

#define K0 0x5a827999
#define K1 0x6ed9eba1
#define K2 0x8f1bbcdc
#define K3 0xca62c1d6

#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)))

// called from 0 to 15
#define R0(a, b, c, d, e, f, i, k, buf)                                 \
    e = LEFT_ROTATE(a, 5) + f(b, c, d) + e + buf[i] + k;                \
    b = LEFT_ROTATE(b, 30)

// called from 16 to 79
#define R1(a, b, c, d, e, f, i, k, buf)                                 \
    buf[i] = buf[(i + 13) & 0xf] ^ buf[(i + 8) & 0xf] ^                 \
             buf[(i +  2) & 0xf] ^ buf[(i + 0) & 0xf];                  \
    e = LEFT_ROTATE(a, 5) + f(b, c, d) + e + buf[i] + k;                \
    b = LEFT_ROTATE(b, 30)

uint32_t loadBigEndian(uint32_t x)
{
    x = (x << 16) | (x >> 16);
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
    return x;
}

static void CHashLib_SHA0_process_chunk(CHashLib_sha0_ctx_t *ctx)
{
    uint32_t tmp_a = ctx->a;
    uint32_t tmp_b = ctx->b;
    uint32_t tmp_c = ctx->c;
    uint32_t tmp_d = ctx->d;
    uint32_t tmp_e = ctx->e;

    uint32_t *buffer = (uint32_t*) ctx->buffer;
    uint32_t i = 0;
    for (; i < 16; i++) {
        buffer[i] = loadBigEndian(buffer[i]);
    }

    R0(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F0,  0, K0, buffer);
    R0(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F0,  1, K0, buffer);
    R0(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F0,  2, K0, buffer);
    R0(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F0,  3, K0, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F0,  4, K0, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F0,  5, K0, buffer);
    R0(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F0,  6, K0, buffer);
    R0(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F0,  7, K0, buffer);
    R0(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F0,  8, K0, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F0,  9, K0, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F0, 10, K0, buffer);
    R0(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F0, 11, K0, buffer);
    R0(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F0, 12, K0, buffer);
    R0(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F0, 13, K0, buffer);
    R0(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F0, 14, K0, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F0, 15, K0, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F0,  0, K0, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F0,  1, K0, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F0,  2, K0, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F0,  3, K0, buffer);

    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F1,  4, K1, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F1,  5, K1, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F1,  6, K1, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F1,  7, K1, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F1,  8, K1, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F1,  9, K1, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F1, 10, K1, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F1, 11, K1, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F1, 12, K1, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F1, 13, K1, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F1, 14, K1, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F1, 15, K1, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F1,  0, K1, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F1,  1, K1, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F1,  2, K1, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F1,  3, K1, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F1,  4, K1, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F1,  5, K1, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F1,  6, K1, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F1,  7, K1, buffer);

    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F2,  8, K2, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F2,  9, K2, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F2, 10, K2, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F2, 11, K2, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F2, 12, K2, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F2, 13, K2, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F2, 14, K2, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F2, 15, K2, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F2,  0, K2, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F2,  1, K2, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F2,  2, K2, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F2,  3, K2, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F2,  4, K2, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F2,  5, K2, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F2,  6, K2, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F2,  7, K2, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F2,  8, K2, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F2,  9, K2, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F2, 10, K2, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F2, 11, K2, buffer);

    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F3, 12, K3, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F3, 13, K3, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F3, 14, K3, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F3, 15, K3, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F3,  0, K3, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F3,  1, K3, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F3,  2, K3, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F3,  3, K3, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F3,  4, K3, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F3,  5, K3, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F3,  6, K3, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F3,  7, K3, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F3,  8, K3, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F3,  9, K3, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F3, 10, K3, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, tmp_e, F3, 11, K3, buffer);
    R1(tmp_e, tmp_a, tmp_b, tmp_c, tmp_d, F3, 12, K3, buffer);
    R1(tmp_d, tmp_e, tmp_a, tmp_b, tmp_c, F3, 13, K3, buffer);
    R1(tmp_c, tmp_d, tmp_e, tmp_a, tmp_b, F3, 14, K3, buffer);
    R1(tmp_b, tmp_c, tmp_d, tmp_e, tmp_a, F3, 15, K3, buffer);

    ctx->a += tmp_a;
    ctx->b += tmp_b;
    ctx->c += tmp_c;
    ctx->d += tmp_d;
    ctx->e += tmp_e;
}

void CHashLib_SHA0_init(CHashLib_sha0_ctx_t *ctx)
{
    ctx->length = 0;
    ctx->a = 0x67452301;
    ctx->b = 0xefcdab89;
    ctx->c = 0x98badcfe;
    ctx->d = 0x10325476;
    ctx->e = 0xc3d2e1f0;
}

void CHashLib_SHA0_update(CHashLib_sha0_ctx_t *ctx, const unsigned char *data, size_t length)
{
    while (length > 0) {
        uint32_t currentPos = ctx->length & 63;
        uint32_t diff = 64 - currentPos;
        if (diff <= length) {
            memcpy(ctx->buffer + currentPos, data, diff);
            ctx->length += diff;
            length -= diff;
            data += diff;

            CHashLib_SHA0_process_chunk(ctx);
        } else {
            memcpy(ctx->buffer + currentPos, data, length);
            ctx->length += length;
            return;
        }
    }
}

void CHashLib_SHA0_final(CHashLib_sha0_ctx_t *ctx, unsigned char output[20])
{
    // prepare original length in bits
    unsigned char bitsArray[8];
    uint64_t bits = ctx->length << 3;
    CHashLib_encode_uint32(loadBigEndian((uint32_t) (bits >>  0)), bitsArray + 4);
    CHashLib_encode_uint32(loadBigEndian((uint32_t) (bits >> 32)), bitsArray + 0);

    // append padding
    uint32_t currentPos = ctx->length & 63;
    CHashLib_SHA0_update(ctx, CHashLib_padding,
        currentPos < 56 ? (56 - currentPos) : (120 - currentPos));

    // append original length in bits
    CHashLib_SHA0_update(ctx, bitsArray, 8);

    // store the hash in hex
    CHashLib_encode_uint32(loadBigEndian(ctx->a), output +  0);
    CHashLib_encode_uint32(loadBigEndian(ctx->b), output +  4);
    CHashLib_encode_uint32(loadBigEndian(ctx->c), output +  8);
    CHashLib_encode_uint32(loadBigEndian(ctx->d), output + 12);
    CHashLib_encode_uint32(loadBigEndian(ctx->e), output + 16);
}

void CHashLib_SHA0_hash(const unsigned char *data, size_t length, unsigned char output[20])
{
    CHashLib_sha0_ctx_t ctx;

    CHashLib_SHA0_init(&ctx);
    CHashLib_SHA0_update(&ctx, data, length);
    CHashLib_SHA0_final(&ctx, output);
}
