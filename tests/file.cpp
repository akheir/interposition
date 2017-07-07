#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <memory>

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
    int fd_ = open("f1.txt", O_WRONLY | O_APPEND |O_CREAT, 0644);
    if(fd_ < 0)
        return 1;
 
    if(::write(fd_,"This will be output to testfile.txt\n", 36) != 36)
    {
        return 2;
    }

    ::close(fd_);

    fd_ = ::open("f1.txt", O_RDONLY);
    std::vector<char> result;
    int count = 10;
    std::unique_ptr<char> sp(new char[count]);

    ssize_t len = ::pread(fd_, sp.get(), count, 15);
    result.assign(sp.get(), sp.get() + len);

    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result[i];
    }
    std::cout << std::endl;

    struct stat fileStat;
    ::fstat(fd_, &fileStat);
    std::cout << "File size is " << fileStat.st_size << std::endl;
    ::close(fd_);

//    ::unlink("f1.txt");

 
    return 0;
}
