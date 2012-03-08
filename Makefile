INCLUDE_FLAGS =  -I/usr/include/python2.6
INCLUDE_FLAGS += -I/usr/include/Poco
INCLUDE_FLAGS += -Iinc

LIB_FLAGS =  -lboost
LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6
LIB_FLAGS += -lPocoFoundation


PYSOURCE      = src/InterfaceWrapper.cpp
SVCSOURCE     = svc/DllSvc.cpp
EXESOURCE     = test/test.cpp
ALGSOURCE     = alg/ImpInterface.cpp 

SVCLIB  = test/libInterface.so
PYLIB   = test/PyInterface.so
ALGLIB  = test/libImpInterface.so

all: ${ALGLIB} ${SVCLIB} ${EXESOURCE} ${PYLIB} 
	g++ ${INCLUDE_FLAGS} -L test -lImpInterface -lInterface ${LIB_FLAGS}  ${EXESOURCE} -o test/test.exe

${PYLIB}: ${PYSOURCE} 
	g++ ${INCLUDE_FLAGS} -L test -lImpInterface -lInterface ${LIB_FLAGS}  ${PYSOURCE} -shared -o test/PyInterface.so

${SVCLIB}:${SVCSOURCE} 
	g++ ${INCLUDE_FLAGS} ${LIB_FLAGS} ${SVCSOURCE}  -shared -o test/libInterface.so

${ALGLIB}: ${ALGSOURCE}
	g++ ${INCLUDE_FLAGS} ${LIB_FLAGS}  ${ALGSOURCE} -shared -o test/libImpInterface.so

clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe 
