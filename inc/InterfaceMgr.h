#ifndef INTERFACEMGR_H
#define INTERFACEMGR_H

// std
#include <string>
#include <map>
#include <algorithm>

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
      IInterface* ifacePtr = NULL;
      if (ifaceType == "Imp2Interface") ifacePtr = dynamic_cast<IInterface*>(new  Imp2Interface(ifaceName));
      if (ifaceType == "ImpInterface")  ifacePtr = dynamic_cast<IInterface*>(new   ImpInterface(ifaceName));
      ifacesMap.insert(std::map<std::string,IInterface*>::value_type(ifaceName, ifacePtr));
      return ifacePtr;
    };
    IInterface* getInterface(std::string ifaceName){
       std::map<std::string,IInterface*>::iterator  ifacePair = ifacesMap.find(ifaceName);
      return (ifacePair == ifacesMap.end()) ? NULL : ifacePair->second;
    }
    string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};
  private:
    std::map<std::string, IInterface*> ifacesMap;
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
