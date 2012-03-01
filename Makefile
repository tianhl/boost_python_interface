INCLUDE_FLAGS =  -I/usr/include/python2.6
INCLUDE_FLAGS += -I/usr/include/Poco

LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6
LIB_FLAGS += -LPoco/Libraries
LIB_FLAGS += -lPocoFoundation


WRAPPERSOURCE = src/InterfaceWrapper.cpp
KERNELSOURCE  = src/InterfaceMgr.cpp src/LibraryMgr.cpp
CPPEXESOURCE  = test/test.cpp
#APPSOURCE     = app/ImpInterface.cpp 

KERNEL = test/libInterface.so
PYLIB  = test/PyInterface.so
#APP    = app/libImpInterface.so

all:${PYLIB} ${KERNEL} ${CPPEXESOURCE} 
	g++ ${INCLUDE_FLAGS} -L test -lInterface  ${LIB_FLAGS}  ${CPPEXESOURCE} -o test/test.exe

${PYLIB}:${KERNEL} ${WRAPPERSOURCE}
	g++ ${INCLUDE_FLAGS}  -L test -lInterface ${WRAPPERSOURCE} ${LIB_FLAGS} -shared -o test/PyInterface.so

${KERNEL}:${KERNELSOURCE} 
	g++ ${INCLUDE_FLAGS}    ${KERNELSOURCE} ${LIB_FLAGS} -shared -o test/libInterface.so

#${APP}:${KERNEL} ${APPSOURCE}
#	g++ ${INCLUDE_FLAGS}  ${LIB_FLAGS} -shared -o app/libImpInterface.so

clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe app/*.so
