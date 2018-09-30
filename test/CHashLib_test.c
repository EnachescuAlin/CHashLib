#include "linux_color.h"
#include <stdio.h>
#include <stdint.h>

#if (!defined LITTLE_ENDIAN && !defined BIG_ENDIAN)
#define LITTLE_ENDIAN
#endif

int test_md5();
int test_md4();
int test_md2();

int get_endian_type()
{
    uint32_t a = 0x00000001;
    uint8_t *b = (uint8_t*) &a;
    return b[0];
}

int main()
{
    int ret = 0;

    printf(COLOR_TEXT("************** running tests **************", COLOR_BLUE) "\n");

    int endian_type = get_endian_type();
#ifdef LITTLE_ENDIAN
    if (endian_type == 0) {
        printf(COLOR_TEXT("expected little endian, but detected big endian", COLOR_RED) "\n");
        ret = 1;
        goto end;
    }
#elif defined BIG_ENDIAN
    if (endian_type == 1) {
        printf(COLOR_TEXT("expected big endian, but detected little endian", COLOR_RED) "\n");
        ret = 1;
        goto end;
    }
#else
#error "endian type not defined"
#endif

    ret += test_md5();
    ret += test_md4();
    ret += test_md2();

end:
    printf(COLOR_TEXT("*******************************************", COLOR_BLUE) "\n");

    return ret;
}
