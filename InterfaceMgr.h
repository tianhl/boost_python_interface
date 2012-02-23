#ifndef INTERFACEMGR_H
#define INTERFACEMGR_H


#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "ImpInterface.h"
#include "IInterface.h"

using namespace boost::python;
using namespace std;


class InterfaceMgr:public IInterface{
  public:
    InterfaceMgr(string name = "interfaceMgr"):IInterface(name){};
    IInterface* create(string name){ 
      return dynamic_cast<IInterface*>(new  ImpInterface(name));
    };
    string getName(){return name;}
};


class InterfaceMgr_callback:public InterfaceMgr{
  public:
    InterfaceMgr_callback(PyObject *p, string name) : self(p), InterfaceMgr(name) {}  //  default construtor
    IInterface* create(string name){ return boost::python::call_method<IInterface*>(self, "create", name); }
    static IInterface*  default_create(InterfaceMgr& self_, string name) { return self_.InterfaceMgr::create(name);}  // necessary
    string getName(){ return boost::python::call_method<string>(self, "getName"); }
    static string  default_getName(InterfaceMgr& self_) { return self_.InterfaceMgr::getName();}  // necessary
  private:
    PyObject *self;
};
#endif  // IINTERFACEMGR_H
