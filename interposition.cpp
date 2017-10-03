//  Copyright (c) 2017 Alireza Kheirkhahang
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h> 

#ifdef __cplusplus
} //extern "C" {
#endif

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#define FORWARD_DECLARE(ret,name,args) \
	ret (*__real_ ## name)args = NULL;
#define MAP(func, ret) \
	if (!(__real_ ## func)) { \
		__real_ ## func = (ret) dlsym(RTLD_NEXT, #func); \
 		if (!(__real_ ## func)) \
 		std::cout  << "Failed to link symbol: " << #func << std::endl; \
	}
#if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
    #define DLL_PUBLIC
    #define DLL_LOCAL
#endif

/*
 * File manipulation functions
 *
 * open, close, creat, read, write, close, pread, pwrite
 *
*/
FORWARD_DECLARE(int, creat, (const char *path, mode_t mode));
FORWARD_DECLARE(int, open, (const char *path, int flags, ...));
FORWARD_DECLARE(int, close, (int fd));
FORWARD_DECLARE(int, unlink, (const char *pathname));
FORWARD_DECLARE(ssize_t, write, (int fd, const void *buf, size_t count));
FORWARD_DECLARE(ssize_t, read, (int fd, void *buf, size_t count));
FORWARD_DECLARE(ssize_t, pread, (int fd, void *buf, size_t count, off_t offset));
FORWARD_DECLARE(ssize_t, pwrite, (int fd, const void *buf, size_t count, off_t offset));

__attribute__ ((noreturn)) FORWARD_DECLARE(void, exit, (int status)) ;

FORWARD_DECLARE(FILE *, fopen, (const char *path, const char *mode));

#ifdef __cplusplus
extern "C" {
#endif

DLL_PUBLIC int open(const char *path, int flags, ...) {
	MAP(open,int (*)(const char*, int, ...));

    std::cout << "Intercepting a call to open \"" << path << '\"' << std::endl;

    int ret = 0;

	if ((flags & O_CREAT) == O_CREAT) {
		va_list argf;
		va_start(argf, flags);
		mode_t mode = va_arg(argf, mode_t);
		va_end(argf);
		ret = __real_open(path, flags, mode);
	} else {
		ret = __real_open(path, flags);
	}

    std::cout << path << " opened successfully with fd: \"" << ret << '\"' << std::endl;

	return ret;
}

DLL_PUBLIC int creat(const char* path, mode_t mode) {

    std::cout << "Intercepting a call to creat \"" << path << '\"' << std::endl;

    int ret = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

    std::cout << path << " created successfully with fd: \"" << ret << '\"' << std::endl;

    return ret;
}

DLL_PUBLIC int close(int fd) {
    MAP(close,int (*)(int));

    std::cout << "Intercepting a call to close \"" << fd << '\"' << std::endl;

    int ret = __real_close(fd);

    return ret;
}

DLL_PUBLIC int unlink(const char *pathname) {
    MAP(unlink, int (*)(const char *));

    std::cout << "Intercepting a call to unlink \"" << pathname << '\"' << std::endl;

    int ret = 0;
    ret = __real_unlink(pathname);

    return ret;
}

DLL_PUBLIC ssize_t write(int fd, const void *buf, size_t count) {
    MAP(write,ssize_t (*)(int, const void*, size_t));

    std::cout << "Intercepting a call to write "
              << count << " bytes on \"" << fd << '\"' << std::endl;

    ssize_t ret = 0;
    ret = __real_write(fd, buf, count);

    return ret;
}

DLL_PUBLIC ssize_t read(int fd, void *buf, size_t count) {
    MAP(read, ssize_t(*)(int, void * , size_t));

    std::cout << "Intercepting a call to read "
              << count << " bytes from \"" << fd << '\"' << std::endl;

    ssize_t ret = 0;
    ret = __real_read(fd, buf, count);

    return ret;
}

DLL_PUBLIC ssize_t pread(int fd, void *buf, size_t count, off_t offset) {
    MAP(pread,ssize_t (*)(int, void*, size_t, off_t));

    std::cout << "Intercepting a call to pread "
              << count << " bytes from \"" << fd << '\"' <<
              " on position " << offset << std::endl;

    ssize_t ret = 0;
    ret = __real_pread(fd, buf, count, offset);

    return ret;
}

DLL_PUBLIC ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset) {
    MAP(pwrite,ssize_t (*)(int, const void*, size_t, off_t));

    std::cout << "Intercepting a call to pwrite "
              << count << " bytes on \"" << fd << '\"' <<
              " on position " << offset << std::endl;

    ssize_t ret = 0;
    ret = __real_pwrite(fd, buf, count, offset);

    return ret;
}

DLL_PUBLIC void exit(int status) {
    MAP(exit, void (*)(int));

    std::cout << "Intercepting a call to exit with status = \"" << status << '\"' << std::endl;
    __real_exit(status);

//    return;
}

DLL_PUBLIC FILE * fopen(const char *path, const char *mode) {
	MAP(fopen, FILE *(*)(const char *, const char *));

	std::cout << "fopen: " << path << std::endl;

	return __real_fopen(path, mode);
}

#ifdef __cplusplus
} //extern "C" {
#endif