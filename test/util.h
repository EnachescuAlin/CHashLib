#ifndef __CHASHLIB_TEST_UTIL_H__
#define __CHASHLIB_TEST_UTIL_H__

#include <stddef.h>

/*
 * Transforms a raw buffer in a hexadecimal string. If the @string is too small then
 * the function will transform just a part from @buffer. The function ensures that the
 * string will always be null-terminated (if @stringSize is greater than 0).
 *
 * @param buffer - the raw buffer that is transformed.
 * @param bufferSize - the size of the @buffer.
 * @param string - the string where the hexadecimal string will be stored.
 * @param stringSize - the size of the string, it should be at least 2 * @bufferSize + 1.
 *
 * @return the number of bytes from @buffer that was transformed in hexadecimal.
 */
size_t BufferToHex(
    const unsigned char *buffer,
    size_t bufferSize,
    char *string,
    size_t stringSize
);

#endif
