#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "InterfaceMgr.h"
#include "IInterface.h"


using namespace boost::python;
using namespace std;


//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( overloadsname , classname::methodname, arg_minimum, arg_maximum )
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FM_createOverloader, InterfaceMgr::create, 2, 2) // only 2 arguments

BOOST_PYTHON_MODULE_INIT(interface)
{                                                                                    // need to expose all functions to python
  class_<IInterface_callback,boost::noncopyable>("IInterface", init<string>())
    .def("getName", pure_virtual(&IInterface::getName))                              // for pure virtual function
    .def("getType", &IInterface::getType, &IInterface_callback::default_getType)     // for virtual function
    ;

  class_<InterfaceMgr, boost::noncopyable, boost::shared_ptr<InterfaceMgr_callback> >("InterfaceMgr", init<string>())
    .def("create",  &InterfaceMgr::create, FM_createOverloader()[return_internal_reference<>()])
    .def("getName", &InterfaceMgr_callback::default_getName)
    .def("getType", &InterfaceMgr::getType)
    ;
}
                                                                                                                                                             
