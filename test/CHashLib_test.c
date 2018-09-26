#include "linux_color.h"
#include <stdio.h>

int test_md5();

int main()
{
    printf(COLOR_TEXT("************** running tests **************", COLOR_BLUE) "\n");

    int ret = 0;

    ret += test_md5();

    printf(COLOR_TEXT("*******************************************", COLOR_BLUE) "\n");

    return ret;
}
