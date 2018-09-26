#include "md5.h"

#include <string.h>

static uint32_t CHashLib_md5_precomputed_table[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static uint32_t CHashLib_md5_shift_amounts[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static unsigned char CHashLib_md5_max_padding[64] = {
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define F0(b, c, d) ((b & c) | ((~b) & d))
#define F1(b, c, d) ((d & b) | ((~d) & c))
#define F2(b, c, d) (b ^ c ^ d)
#define F3(b, c, d) (c ^ (b | (~d)))

#define LEFT_ROTATE(x, c) ((x << c) | (x >> (32 - c)))

#define R(a, b, c, d, f, i, j, buf)                             \
    f += a + CHashLib_md5_precomputed_table[i] + buf[j];        \
    a = d;                                                      \
    d = c;                                                      \
    c = b;                                                      \
    b += LEFT_ROTATE(f, CHashLib_md5_shift_amounts[i])

#define R0(a, b, c, d, f, i, buf)                               \
    f = F0(b, c, d);                                            \
    R(a, b, c, d, f, i, (i), buf);

#define R1(a, b, c, d, f, i, buf)                               \
    f = F1(b, c, d);                                            \
    R(a, b, c, d, f, i, ((5 * i + 1) % 16), buf);

#define R2(a, b, c, d, f, i, buf)                               \
    f = F2(b, c, d);                                            \
    R(a, b, c, d, f, i, ((3 * i + 5) % 16), buf);

#define R3(a, b, c, d, f, i, buf)                               \
    f = F3(b, c, d);                                            \
    R(a, b, c, d, f, i, ((7 * i) % 16), buf);

static void CHashLib_MD5_process_chunk(CHashLib_md5_ctx_t *ctx)
{
    uint32_t f;
    uint32_t tmp_a0 = ctx->a0;
    uint32_t tmp_b0 = ctx->b0;
    uint32_t tmp_c0 = ctx->c0;
    uint32_t tmp_d0 = ctx->d0;

    uint32_t *buffer = (uint32_t*) ctx->buffer;

    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  0, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  1, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  2, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  3, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  4, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  5, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  6, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  7, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  8, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f,  9, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 10, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 11, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 12, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 13, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 14, buffer);
    R0(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 15, buffer);

    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 16, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 17, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 18, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 19, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 20, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 21, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 22, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 23, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 24, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 25, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 26, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 27, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 28, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 29, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 30, buffer);
    R1(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 31, buffer);

    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 32, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 33, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 34, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 35, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 36, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 37, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 38, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 39, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 40, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 41, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 42, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 43, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 44, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 45, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 46, buffer);
    R2(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 47, buffer);

    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 48, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 49, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 50, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 51, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 52, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 53, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 54, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 55, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 56, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 57, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 58, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 59, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 60, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 61, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 62, buffer);
    R3(tmp_a0, tmp_b0, tmp_c0, tmp_d0, f, 63, buffer);

    ctx->a0 += tmp_a0;
    ctx->b0 += tmp_b0;
    ctx->c0 += tmp_c0;
    ctx->d0 += tmp_d0;
}

static void CHashLib_MD5_uint32_to_hex(uint32_t value, char *buffer)
{
    static const char hexChars[] = "0123456789abcdef";

    buffer[0] = hexChars[(value >>  4) & 0xF];
    buffer[1] = hexChars[(value >>  0) & 0xF];
    buffer[2] = hexChars[(value >> 12) & 0xF];
    buffer[3] = hexChars[(value >>  8) & 0xF];
    buffer[4] = hexChars[(value >> 20) & 0xF];
    buffer[5] = hexChars[(value >> 16) & 0xF];
    buffer[6] = hexChars[(value >> 28) & 0xF];
    buffer[7] = hexChars[(value >> 24) & 0xF];
}

void CHashLib_MD5_init(CHashLib_md5_ctx_t *ctx)
{
    memset(ctx->buffer, 0, 64);
    ctx->length = 0;

    ctx->a0 = 0x67452301;
    ctx->b0 = 0xefcdab89;
    ctx->c0 = 0x98badcfe;
    ctx->d0 = 0x10325476;
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

void CHashLib_MD5_final(CHashLib_md5_ctx_t *ctx, char output[32])
{
    // prepare original length in bits
    unsigned char bitsArray[8];
    uint64_t bits = ctx->length << 3;
    uint32_t index;
    for (index = 0; index < 8; index++) {
        bitsArray[index] = (bits >> (index * 8)) & 0xff;
    }

    // append padding
    uint32_t currentPos = ctx->length & 63;
    CHashLib_MD5_update(ctx, CHashLib_md5_max_padding,
        currentPos < 56 ? (56 - currentPos) : (120 - currentPos));

    // append original length in bits
    CHashLib_MD5_update(ctx, bitsArray, 8);

    // store the hash in hex
    CHashLib_MD5_uint32_to_hex(ctx->a0, output +  0);
    CHashLib_MD5_uint32_to_hex(ctx->b0, output +  8);
    CHashLib_MD5_uint32_to_hex(ctx->c0, output + 16);
    CHashLib_MD5_uint32_to_hex(ctx->d0, output + 24);
}

void CHashLib_MD5_hash(const unsigned char *data, size_t length, char output[32])
{
    CHashLib_md5_ctx_t ctx;

    CHashLib_MD5_init(&ctx);
    CHashLib_MD5_update(&ctx, data, length);
    CHashLib_MD5_final(&ctx, output);
}