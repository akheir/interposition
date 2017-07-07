#include <iostream>
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifdef __cplusplus
} //extern "C" {
#endif

int main()
{
    FILE *fd = fopen("test_file", "r");
    if (!fd) {
        printf("fopen() returned NULL\n");
        return 1;
    }

    return 0;
}