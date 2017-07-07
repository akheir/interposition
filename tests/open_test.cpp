#include <iostream>
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
} //extern "C" {
#endif

int main()
{
    int fd_ = open("test1.txt", O_WRONLY | O_APPEND |O_CREAT, 0644);
    if(fd_ < 0)
        return 1;

    return 0;
}