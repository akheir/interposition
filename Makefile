CC=g++

OPTS = -g -fPIC -shared -fvisibility=hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
LINKOPTS = -g -fPIC -shared -fvisibility=hidden -Wl,-soname,libinterposition.so.1 -o libinterposition.so.1.0.1 -lpthread -ldl

all: libinterposition

libinterposition:
	rm -Rf *.so* # clean up any symlinks
	$(CC) $(OPTS) -O3 -c interposition.cpp
	$(CC) $(LINKOPTS) -O3 interposition.o
	ln -s libinterposition.so.1.0.1 libinterposition.so.1
	ln -s libinterposition.so.1 libinterposition.so

clean:
	rm -f *.o *.so *.so.*