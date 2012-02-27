#ifndef INTERFACEMGR_H
#define INTERFACEMGR_H

// std
#include <string>

// boost
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

// interfaceMgr
#include "../inc/ImpInterface.h"
#include "../inc/IInterface.h"

using namespace std;


class InterfaceMgr:public IInterface{
  public:
    InterfaceMgr(string name = "cppInterfaceMgr"):IInterface(name){};
    IInterface* create(const string& ifaceType, const string& ifaceName){ 
      if (ifaceType == "Imp2Interface") return dynamic_cast<IInterface*>(new  Imp2Interface(ifaceName));
      if (ifaceType == "ImpInterface")  return dynamic_cast<IInterface*>(new   ImpInterface(ifaceName));
    };
    string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};
};

//using namespace boost::python;
//
//class InterfaceMgr_callback:public InterfaceMgr{
//  public:
//    InterfaceMgr_callback(PyObject *p, string name = "pyInterfaceMgr") : self(p), InterfaceMgr(name) {}  //  default construtor
//  private:
//    PyObject *self;
//};
#endif  // IINTERFACEMGR_H
