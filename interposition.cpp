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

FORWARD_DECLARE(int, open, (const char *path, int flags, ...));
FORWARD_DECLARE(FILE *, fopen, (const char *path, const char *mode));

int open(const char *path, int flags, ...) {
	MAP(open,int (*)(const char*, int, ...));

	printf("my open\n");
	int ret;

	if ((flags & O_CREAT) == O_CREAT) {
		va_list argf;
		va_start(argf, flags);
		mode_t mode = va_arg(argf, mode_t);
		va_end(argf);
		ret = __real_open(path, flags, mode);
	} else {
		ret = __real_open(path, flags);
	}

	std::cout << "opening file: " << std::endl;

	return ret;
}

FILE * fopen(const char *path, const char *mode) {
	MAP(fopen, FILE *(*)(const char *, const char *));

	std::cout << "fopen: " << path << std::endl;

	return __real_fopen(path, mode);
}