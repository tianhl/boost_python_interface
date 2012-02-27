PYTHON_INCLUDE_FLAGS = -I/usr/include/python2.6

LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6

SOURCE = src/*.cpp
LIB = test/libInterface.so
EXE = test/test.cpp

all:${LIB} ${EXE}
	g++ -L test -lInterface ${LIB_FLAGS}  ${EXE} -o test/test.exe

${LIB}:${SOURCE}
	g++ ${PYTHON_INCLUDE_FLAGS} ${SOURCE} ${LIB_FLAGS} -shared -o test/libInterface.so

clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe
