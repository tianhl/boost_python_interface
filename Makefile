INCLUDE_FLAGS =  -I/usr/include/python2.6
INCLUDE_FLAGS += -I/usr/include/Poco
INCLUDE_FLAGS += -Iinc

LIB_FLAGS =  -lboost
LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6
LIB_FLAGS += -lPocoFoundation

SHARE := -fPIC -shared -o
CC    := g++

PYSOURCE      = src/InterfaceWrapper.cpp
SVCSOURCE     = svc/*.cpp  svc/*.h
EXESOURCE     = test/test.cpp
ALGSOURCE     = alg/*.cpp alg/*.h 
KERNELSOURCE  = inc/*.h

SVCLIB  = test/libSvsBPI.so
PYLIB   = test/PyInterface.so
ALGLIB  = test/libAlgBPI.so

all: ${ALGLIB} ${SVCLIB} ${EXESOURCE} #${PYLIB} 
	${CC} ${INCLUDE_FLAGS} -L test -lSvcBPI -lAlgBPI ${LIB_FLAGS}  ${EXESOURCE} -o test/test.exe

${PYLIB}:${PYSOURCE} ${KERNELSOURCE} 
	${CC} ${INCLUDE_FLAGS} -L test -lSvcBPI -lAlgBPI ${LIB_FLAGS}  ${PYSOURCE} ${SHARE} test/PyInterface.so

${SVCLIB}:${SVCSOURCE} ${KERNELSOURCE}
	${CC} ${INCLUDE_FLAGS} ${LIB_FLAGS} ${SVCSOURCE}  ${SHARE} test/libSvcBPI.so

${ALGLIB}:${ALGSOURCE} ${KERNELSOURCE}
	${CC} ${INCLUDE_FLAGS} ${LIB_FLAGS}  ${ALGSOURCE} ${SHARE} test/libAlgBPI.so

clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe 
