#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "../inc/InterfaceMgr.h"
#include "../inc/IInterface.h"
#include "../inc/SingletionHolder.h"


using namespace boost::python;
using namespace std;


//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( overloadsname , classname::methodname, arg_minimum, arg_maximum )
//http://wiki.python.org/moin/boost.python/FunctionOverloading
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FM_createOverloader, InterfaceMgr::create, 2, 2) // only 2 arguments
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FM_getOverloader, InterfaceMgr::getInterface, 1, 1) // only 1 arguments
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FM_instanceOverloader, IfaceMgr::Instance, 0, 0) // only 1 arguments

BOOST_PYTHON_MODULE_INIT(libInterface)
{                                                                                    // need to expose all functions to python
  class_<IInterface_callback,boost::noncopyable>("IInterface", init<string>())
    .def("getName", pure_virtual(&IInterface::getName))                              // for pure virtual function
    .def("getType", &IInterface::getType, &IInterface_callback::default_getType)     // for virtual function
    ;

  //class_<InterfaceMgr, boost::noncopyable, boost::shared_ptr<InterfaceMgr_callback> >("InterfaceMgr", init<string>())
  //class_<InterfaceMgr, boost::noncopyable>("InterfaceMgr", init<string>())
  //class_<InterfaceMgr>("InterfaceMgr", init<string>())
  class_<InterfaceMgr>("InterfaceMgr", no_init)
//    .def("instance", &IfaceMgr::Instance, FM_instanceOverloader()[return_internal_reference<>()])
    .def("create",   &InterfaceMgr::create, FM_createOverloader()[return_internal_reference<>()])  // necessary
    .def("getInterface",   &InterfaceMgr::getInterface, FM_getOverloader()[return_internal_reference<>()])  // necessary
    .def("getName",  &InterfaceMgr::getName)
    .def("sayHello", &InterfaceMgr::sayHello)
    .def("getType",  &InterfaceMgr::getType)
    ;

////  def("create", create, return_value_policy<manage_new_object>());
//  class_<IfaceMgrWrapper>("IfaceMgr")
//    //.staticmethod("Instance", &IfaceMgr::Instance, FM_instanceOverloader()[return_value_policy<manage_new_object>()])
//    .def("Instance", &IfaceMgrWrapper::Instance, FM_instanceOverloader()[return_value_policy<manage_new_object>()])
//    //.staticmethod("Instance", &IfaceMgrWrapper::Instance, FM_instanceOverloader()[  return_internal_reference<>()  ])
//    ;
//
}
                                                                                                                                                             
