INCLUDE_FLAGS =  -I/usr/include/python2.6
INCLUDE_FLAGS += -I/usr/include/Poco
INCLUDE_FLAGS += -Iinc

LIB_FLAGS =  -lboost
LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6
LIB_FLAGS += -lPocoFoundation


WRAPPERSOURCE = src/InterfaceWrapper.cpp
KERNELSOURCE  = src/InterfaceMgr.cpp src/LibraryMgr.cpp
CPPEXESOURCE  = test/test.cpp
APPSOURCE     = app/ImpInterface.cpp 

KERNEL = test/libInterface.so
PYLIB  = test/PyInterface.so
APP    = test/libImpInterface.so

#all:${PYLIB} ${KERNEL} ${CPPEXESOURCE}  ${APP}
#	g++ ${INCLUDE_FLAGS} -L test -lInterface  -lImpInterface  ${LIB_FLAGS}  ${CPPEXESOURCE} -o test/test.exe
#
all: ${KERNELSOURCE} ${CPPEXESOURCE}  ${APPSOURCE}
	g++ ${INCLUDE_FLAGS}  ${LIB_FLAGS} ${APPSOURCE} ${KERNELSOURCE}   ${CPPEXESOURCE} -o test/test.exe

#${PYLIB}:${KERNEL} ${WRAPPERSOURCE} ${APP}
#	g++ ${INCLUDE_FLAGS}  -L test -lInterface -lImpInterface  ${LIB_FLAGS}  ${WRAPPERSOURCE} -shared -o test/PyInterface.so
#
#${KERNEL}:${KERNELSOURCE} 
#	g++ ${INCLUDE_FLAGS} ${LIB_FLAGS} ${KERNELSOURCE} -shared -o test/libInterface.so
#
#${APP}: ${APPSOURCE}
#	g++ ${INCLUDE_FLAGS} ${LIB_FLAGS}  -shared -o test/libImpInterface.so
#
clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe 
