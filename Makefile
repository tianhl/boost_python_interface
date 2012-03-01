INCLUDE_FLAGS =  -I/usr/include/python2.6
INCLUDE_FLAGS += -I/usr/include/Poco
INCLUDE_FLAGS += -I/home/tianhl/workarea/git/boost_python_interface/inc

LIB_FLAGS =  -lboost_python
LIB_FLAGS += -lpython2.6
LIB_FLAGS += -LPoco/Libraries
LIB_FLAGS += -lPocoFoundation


WRAPPERSOURCE = src/InterfaceWrapper.cpp
KERNELSOURCE  = src/InterfaceMgr.cpp src/LibraryMgr.cpp
#APPSOURCE     = app/ImpInterface.cpp 

KERNEL = test/libInterface.so
PYLIB  = test/PyInterface.so
EXE    = test/test.cpp
#APP    = app/libImpInterface.so

all:${PYLIB} ${KERNEL} ${EXE} 
	g++ ${INCLUDE_FLAGS} -L test -lInterface  ${LIB_FLAGS}  ${EXE} -o test/test.exe

${PYLIB}:${KERNEL} ${WRAPPERSOURCE}
	g++ ${INCLUDE_FLAGS}  -L test -lInterface ${WRAPPERSOURCE} ${LIB_FLAGS} -shared -o test/PyInterface.so

${KERNEL}:${KERNELSOURCE} ${APP}
	g++ ${INCLUDE_FLAGS}    ${KERNELSOURCE} ${LIB_FLAGS} -shared -o test/libInterface.so

#${APP}:${KERNEL} ${APPSOURCE}
#	g++ ${INCLUDE_FLAGS}  ${LIB_FLAGS} -shared -o app/libImpInterface.so

clean:
	rm -f test/*.o test/*.out test/*.so test/*.exe app/*.so
