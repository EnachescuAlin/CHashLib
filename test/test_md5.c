#include "md5.h"
#include <stdio.h>
#include <string.h>

#include "linux_color.h"

typedef struct {
    const char *string;
    const char *hash;
} test_case_t;

#define TEST_NAME "test md5"

int test_md5()
{
    static test_case_t testCases[] = {
        { "", "d41d8cd98f00b204e9800998ecf8427e" }
    };

    int failed = 0;
    size_t i = 0;
    char hash[33] = { 0 };

    for (; i < (sizeof(testCases) / sizeof(test_case_t)); i++) {
        CHashLib_MD5_hash(
            (const unsigned char*) testCases[i].string,
            strlen(testCases[i].string),
            hash
        );
        if (memcmp(hash, testCases[i].hash, 33) != 0) {
            failed++;
        }
    }

    if (failed == 0) {
        printf("%-40s " COLOR_TEXT("OK", COLOR_GREEN) "\n", TEST_NAME);
        return 0;
    }

    printf("%-40s " COLOR_TEXT("FAILED", COLOR_RED) "\n", TEST_NAME);
	return 1;
}
