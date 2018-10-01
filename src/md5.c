#include "md5.h"
#include "utils.h"

#include <string.h>

#define F0(b, c, d) ((b & c) | ((~b) & d))
#define F1(b, c, d) ((d & b) | ((~d) & c))
#define F2(b, c, d) (b ^ c ^ d)
#define F3(b, c, d) (c ^ (b | (~d)))

#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)))

#define R(a, b, c, d, f, i, s, ac, buf)                         \
    f += a + ac + buf[i];                                       \
    a = d;                                                      \
    d = c;                                                      \
    c = b;                                                      \
    b += LEFT_ROTATE(f, s)

#define R0(a, b, c, d, f, i, s, ac, buf)                        \
    f = F0(b, c, d);                                            \
    R(a, b, c, d, f, i, s, ac, buf);

#define R1(a, b, c, d, f, i, s, ac, buf)                        \
    f = F1(b, c, d);                                            \
    R(a, b, c, d, f, i, s, ac, buf);

#define R2(a, b, c, d, f, i, s, ac, buf)                        \
    f = F2(b, c, d);                                            \
    R(a, b, c, d, f, i, s, ac, buf);

#define R3(a, b, c, d, f, i, s, ac, buf)                        \
    f = F3(b, c, d);                                            \
    R(a, b, c, d, f, i, s, ac, buf);

static void CHashLib_MD5_process_chunk(CHashLib_md5_ctx_t *ctx)
{
    uint32_t f;
    uint32_t tmp_a = ctx->a;
    uint32_t tmp_b = ctx->b;
    uint32_t tmp_c = ctx->c;
    uint32_t tmp_d = ctx->d;

    uint32_t *buffer = (uint32_t*) ctx->buffer;

    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  0,  7, 0xd76aa478, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  1, 12, 0xe8c7b756, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  2, 17, 0x242070db, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  3, 22, 0xc1bdceee, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  4,  7, 0xf57c0faf, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  5, 12, 0x4787c62a, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  6, 17, 0xa8304613, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  7, 22, 0xfd469501, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  8,  7, 0x698098d8, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f,  9, 12, 0x8b44f7af, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 10, 17, 0xffff5bb1, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 11, 22, 0x895cd7be, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 12,  7, 0x6b901122, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 13, 12, 0xfd987193, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 14, 17, 0xa679438e, buffer);
    R0(tmp_a, tmp_b, tmp_c, tmp_d, f, 15, 22, 0x49b40821, buffer);

    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  1,  5, 0xf61e2562, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  6,  9, 0xc040b340, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 11, 14, 0x265e5a51, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  0, 20, 0xe9b6c7aa, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  5,  5, 0xd62f105d, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 10,  9, 0x02441453, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 15, 14, 0xd8a1e681, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  4, 20, 0xe7d3fbc8, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  9,  5, 0x21e1cde6, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 14,  9, 0xc33707d6, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  3, 14, 0xf4d50d87, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  8, 20, 0x455a14ed, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 13,  5, 0xa9e3e905, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  2,  9, 0xfcefa3f8, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f,  7, 14, 0x676f02d9, buffer);
    R1(tmp_a, tmp_b, tmp_c, tmp_d, f, 12, 20, 0x8d2a4c8a, buffer);

    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  5,  4, 0xfffa3942, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  8, 11, 0x8771f681, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 11, 16, 0x6d9d6122, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 14, 23, 0xfde5380c, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  1,  4, 0xa4beea44, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  4, 11, 0x4bdecfa9, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  7, 16, 0xf6bb4b60, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 10, 23, 0xbebfbc70, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 13,  4, 0x289b7ec6, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  0, 11, 0xeaa127fa, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  3, 16, 0xd4ef3085, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  6, 23, 0x04881d05, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  9,  4, 0xd9d4d039, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 12, 11, 0xe6db99e5, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f, 15, 16, 0x1fa27cf8, buffer);
    R2(tmp_a, tmp_b, tmp_c, tmp_d, f,  2, 23, 0xc4ac5665, buffer);

    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  0,  6, 0xf4292244, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  7, 10, 0x432aff97, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 14, 15, 0xab9423a7, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  5, 21, 0xfc93a039, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 12,  6, 0x655b59c3, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  3, 10, 0x8f0ccc92, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 10, 15, 0xffeff47d, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  1, 21, 0x85845dd1, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  8,  6, 0x6fa87e4f, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 15, 10, 0xfe2ce6e0, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  6, 15, 0xa3014314, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 13, 21, 0x4e0811a1, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  4,  6, 0xf7537e82, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f, 11, 10, 0xbd3af235, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  2, 15, 0x2ad7d2bb, buffer);
    R3(tmp_a, tmp_b, tmp_c, tmp_d, f,  9, 21, 0xeb86d391, buffer);

    ctx->a += tmp_a;
    ctx->b += tmp_b;
    ctx->c += tmp_c;
    ctx->d += tmp_d;
}

void CHashLib_MD5_init(CHashLib_md5_ctx_t *ctx)
{
    memset(ctx->buffer, 0, 64);
    ctx->length = 0;

    ctx->a = 0x67452301;
    ctx->b = 0xefcdab89;
    ctx->c = 0x98badcfe;
    ctx->d = 0x10325476;
}

void CHashLib_MD5_update(CHashLib_md5_ctx_t *ctx, const unsigned char *data, size_t length)
{
    while (length > 0) {
        uint32_t currentPos = ctx->length & 63;
        uint32_t diff = 64 - currentPos;
        if (diff <= length) {
            memcpy(ctx->buffer + currentPos, data, diff);
            ctx->length += diff;
            length -= diff;
            data += diff;

            CHashLib_MD5_process_chunk(ctx);
        } else {
            memcpy(ctx->buffer + currentPos, data, length);
            ctx->length += length;
            return;
        }
    }
}

void CHashLib_MD5_final(CHashLib_md5_ctx_t *ctx, unsigned char output[16])
{
    // prepare original length in bits
    unsigned char bitsArray[8];
    uint64_t bits = ctx->length << 3;
    CHashLib_encode_uint32((uint32_t) (bits >>  0), bitsArray + 0);
    CHashLib_encode_uint32((uint32_t) (bits >> 32), bitsArray + 4);

    // append padding
    uint32_t currentPos = ctx->length & 63;
    CHashLib_MD5_update(ctx, CHashLib_padding,
        currentPos < 56 ? (56 - currentPos) : (120 - currentPos));

    // append original length in bits
    CHashLib_MD5_update(ctx, bitsArray, 8);

    // store the hash in hex
    CHashLib_encode_uint32(ctx->a, output +  0);
    CHashLib_encode_uint32(ctx->b, output +  4);
    CHashLib_encode_uint32(ctx->c, output +  8);
    CHashLib_encode_uint32(ctx->d, output + 12);
}

void CHashLib_MD5_hash(const unsigned char *data, size_t length, unsigned char output[16])
{
    CHashLib_md5_ctx_t ctx;

    CHashLib_MD5_init(&ctx);
    CHashLib_MD5_update(&ctx, data, length);
    CHashLib_MD5_final(&ctx, output);
}
