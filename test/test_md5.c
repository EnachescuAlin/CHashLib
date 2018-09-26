#include "md5.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *string;
    const char *hash;
} test_case_t;

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
        printf("test md5 - OK\n");
        return 0;
    }

    printf("test md5 - FAILED\n");
	return 1;
}
