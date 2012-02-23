PYTHON_INCLUDE_FLAGS = -I/usr/include/python2.6

LIB_FLAGS = -lboost_python

SOURCE = ImpInterface.cpp interface.cpp

all:${SOURCE}
	g++ ${PYTHON_INCLUDE_FLAGS} ${SOURCE} ${LIB_FLAGS} -shared -o interface.so
clean:
	rm -f interface  *.o *.out *.so

