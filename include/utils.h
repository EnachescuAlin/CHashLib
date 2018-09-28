#ifndef __CHASHLIB_UTILS_H__
#define __CHASHLIB_UTILS_H__

#include <stdint.h>

extern unsigned char CHashLib_padding[64];

void CHashLib_encode_uint32(uint32_t value, unsigned char *buffer);

#endif
