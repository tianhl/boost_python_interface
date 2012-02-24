#ifndef INTERFACEMGR_H
#define INTERFACEMGR_H

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

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
    InterfaceMgr(string name = "cppInterfaceMgr"):IInterface(name){};
    IInterface* create(const string& ifacType, const string& ifacName){ 
      //transform(type.begin(), type.end(), type.begin(), toupper);
      if (ifacType == "Imp2Interface") return dynamic_cast<IInterface*>(new  Imp2Interface(ifacName));
      if (ifacType == "ImpInterface")  return dynamic_cast<IInterface*>(new   ImpInterface(ifacName));
    };
    string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
};


class InterfaceMgr_callback:public InterfaceMgr{
  public:
    InterfaceMgr_callback(PyObject *p, string name = "pyInterfaceMgr") : self(p), InterfaceMgr(name) {}  //  default construtor
    IInterface* create(string type, string name){ return boost::python::call_method<IInterface*>(self, "create", type, name); }
    static IInterface*  default_create(InterfaceMgr& self_, string type, string name) { return self_.InterfaceMgr::create(type, name);}  // necessary
    string getName(){ return boost::python::call_method<string>(self, "getName"); }
    static string  default_getName(InterfaceMgr& self_) { return self_.InterfaceMgr::getName();}  // necessary
  private:
    PyObject *self;
};
#endif  // IINTERFACEMGR_H
