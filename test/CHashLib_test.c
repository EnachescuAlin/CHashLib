#include "linux_color.h"
#include <stdio.h>

int test_md5();
int test_md4();
int test_md2();

int main()
{
    printf(COLOR_TEXT("************** running tests **************", COLOR_BLUE) "\n");

    int ret = 0;

    ret += test_md5();
    ret += test_md4();
    ret += test_md2();

    printf(COLOR_TEXT("*******************************************", COLOR_BLUE) "\n");

    return ret;
}
