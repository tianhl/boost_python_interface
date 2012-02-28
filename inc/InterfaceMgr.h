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
#include "../inc/SingletionHolder.h"
#include "../inc/ImpInterface.h"
#include "../inc/IInterface.h"

using namespace std;


class InterfaceMgr:public IInterface{
  public:

    IInterface* create(const string& ifaceType, const string& ifaceName){ 
      IInterface* ifacePtr = NULL;
      if (ifaceType == "Imp2Interface") ifacePtr = dynamic_cast<IInterface*>(new  Imp2Interface(ifaceName));
      if (ifaceType == "ImpInterface")  ifacePtr = dynamic_cast<IInterface*>(new   ImpInterface(ifaceName));
      ifaces_map.insert(std::map<std::string,IInterface*>::value_type(ifaceName, ifacePtr));
      return ifacePtr;
    };

    IInterface* getInterface(std::string ifaceName){
       std::map<std::string,IInterface*>::iterator  ifacePair = ifaces_map.find(ifaceName);
      return (ifacePair == ifaces_map.end()) ? NULL : ifacePair->second;
    }

    // for test
    string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};
  private:
    friend struct CreateUsingNew<InterfaceMgr>;
    InterfaceMgr():IInterface("cppInterfaceMgr"){};
    std::map<std::string, IInterface*> ifaces_map;
};

//template class SingletonHolder<InterfaceMgr>;
typedef SingletonHolder<InterfaceMgr> IfaceMgr;

//class IfaceMgrWrapper{
//  public:
//    InterfaceMgr& Instance(){return IfaceMgr::Instance();}
//}

#endif  // IINTERFACEMGR_H
