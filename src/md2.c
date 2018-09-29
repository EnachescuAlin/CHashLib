#include "md2.h"

#include <string.h>

static unsigned char CHashLib_MD2_random_substitution[256] = {
     41,  46,  67, 201, 162, 216, 124,   1,  61,  54,  84, 161, 236, 240,   6,  19,
     98, 167,   5, 243, 192, 199, 115, 140, 152, 147,  43, 217, 188,  76, 130, 202,
     30, 155,  87,  60, 253, 212, 224,  22, 103,  66, 111,  24, 138,  23, 229,  18,
    190,  78, 196, 214, 218, 158, 222,  73, 160, 251, 245, 142, 187,  47, 238, 122,
    169, 104, 121, 145,  21, 178,   7,  63, 148, 194,  16, 137,  11,  34,  95,  33,
    128, 127,  93, 154,  90, 144,  50,  39,  53,  62, 204, 231, 191, 247, 151,   3,
    255,  25,  48, 179,  72, 165, 181, 209, 215,  94, 146,  42, 172,  86, 170, 198,
     79, 184,  56, 210, 150, 164, 125, 182, 118, 252, 107, 226, 156, 116,   4, 241,
     69, 157, 112,  89, 100, 113, 135,  32, 134,  91, 207, 101, 230,  45, 168,   2,
     27,  96,  37, 173, 174, 176, 185, 246,  28,  70,  97, 105,  52,  64, 126,  15,
     85,  71, 163,  35, 221,  81, 175,  58, 195,  92, 249, 206, 186, 197, 234,  38,
     44,  83,  13, 110, 133,  40, 132,   9, 211, 223, 205, 244,  65, 129,  77,  82,
    106, 220,  55, 200, 108, 193, 171, 250,  36, 225, 123,   8,  12, 189, 177,  74,
    120, 136, 149, 139, 227,  99, 232, 109, 233, 203, 213, 254,  59,   0,  29,  57,
    242, 239, 183,  14, 102,  88, 208, 228, 166, 119, 114, 248, 235, 117,  75,  10,
     49,  68,  80, 180, 143, 237,  31,  26, 219, 153, 141,  51, 159,  17, 131,  20
};

static unsigned char* CHashLib_MD2_padding[17] = {
    (unsigned char*) "",
    (unsigned char*) "\001",
    (unsigned char*) "\002\002",
    (unsigned char*) "\003\003\003",
    (unsigned char*) "\004\004\004\004",
    (unsigned char*) "\005\005\005\005\005",
    (unsigned char*) "\006\006\006\006\006\006",
    (unsigned char*) "\007\007\007\007\007\007\007",
    (unsigned char*) "\010\010\010\010\010\010\010\010",
    (unsigned char*) "\011\011\011\011\011\011\011\011\011",
    (unsigned char*) "\012\012\012\012\012\012\012\012\012\012",
    (unsigned char*) "\013\013\013\013\013\013\013\013\013\013\013",
    (unsigned char*) "\014\014\014\014\014\014\014\014\014\014\014\014",
    (unsigned char*) "\015\015\015\015\015\015\015\015\015\015\015\015\015",
    (unsigned char*) "\016\016\016\016\016\016\016\016\016\016\016\016\016\016",
    (unsigned char*) "\017\017\017\017\017\017\017\017\017\017\017\017\017\017\017",
    (unsigned char*) "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
};

static void CHashLib_MD2_process_chunk(CHashLib_md2_ctx_t *ctx, const unsigned char *data)
{
    uint32_t i, j, tmp;
    unsigned char buffer[48];
    unsigned char *ptr;

    memcpy(buffer, ctx->state, 16);
    memcpy(buffer + 16, data, 16);

    ptr = buffer + 32;
    for (i = 0; i < 16; i++) {
        ptr[i] = ctx->state[i] ^ data[i];
    }

    tmp = 0;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 48; j++) {
            tmp = buffer[j] ^= CHashLib_MD2_random_substitution[tmp];
        }
        tmp += i;
        tmp &= 0xff;
    }

    memcpy(ctx->state, buffer, 16);

    tmp = ctx->checksum[15];
    for (i = 0; i < 16; i++) {
        tmp = ctx->checksum[i] ^= CHashLib_MD2_random_substitution[data[i] ^ tmp];
    }

    memset(buffer, 0, 48);
}

void CHashLib_MD2_init(CHashLib_md2_ctx_t *ctx)
{
    ctx->length = 0;
    memset(ctx->state, 0, 16);
    memset(ctx->checksum, 0, 16);
}

void CHashLib_MD2_update(CHashLib_md2_ctx_t *ctx, const unsigned char *data, uint32_t length)
{
    uint32_t diff = 16 - ctx->length;
    if (length >= diff) {
        memcpy(&ctx->buffer[ctx->length], data, diff);
        CHashLib_MD2_process_chunk(ctx, ctx->buffer);

        uint32_t i;
        for (i = diff; i + 15 < length; i += 16) {
            CHashLib_MD2_process_chunk(ctx, data + i);
        }

        uint32_t remainingBytes = length - i;
        if (remainingBytes > 0) {
            memcpy(ctx->buffer, data + i, remainingBytes);
        }
    } else {
        memcpy(&ctx->buffer[ctx->length], data, length);
    }

    ctx->length += length;
    ctx->length &= 0xf;
}

void CHashLib_MD2_final(CHashLib_md2_ctx_t *ctx, unsigned char output[16])
{
    uint32_t paddingLength;

    paddingLength = 16 - ctx->length;
    CHashLib_MD2_update(ctx, CHashLib_MD2_padding[paddingLength], paddingLength);

    CHashLib_MD2_update(ctx, ctx->checksum, 16);

    memcpy(output, ctx->state, 16);
}

void CHashLib_MD2_hash(const unsigned char *data, uint32_t length, unsigned char output[16])
{
    CHashLib_md2_ctx_t ctx;

    CHashLib_MD2_init(&ctx);
    CHashLib_MD2_update(&ctx, data, length);
    CHashLib_MD2_final(&ctx, output);
}
