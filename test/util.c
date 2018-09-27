#include "util.h"

size_t BufferToHex(const unsigned char *buffer, size_t bufferSize,
    char *string, size_t stringSize)
{
    static const char hexChars[] = "0123456789abcdef";

    size_t i = 0, j = 0;
    for (; i < bufferSize && stringSize > 2; i++, stringSize--) {
        string[j++] = hexChars[buffer[i] >> 4];
        string[j++] = hexChars[buffer[i] & 0xf];
    }
    string[j] = '\0';

    return i;
}
