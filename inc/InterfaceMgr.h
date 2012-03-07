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
#include "../inc/IInterface.h"
#include "../inc/LibraryMgr.h"
#include "../inc/DynamicFactory.h"

//#include "../app/ImpInterface.h"

using namespace std;


template<class T>
class InterfaceMgr:public IInterface{
  public:

    T* getInterface(const std::string& ifaceName){
      // why map<std::string, T*>::iterator cannot work?
      return ifaces_map.find(ifaceName) != ifaces_map.end() ?  dynamic_cast<T*>(ifaces_map.find(ifaceName)->second)  : NULL ;
      return NULL;
    };

    IInterface* create(const std::string& className, const std::string& ifaceName){
      T* iface = IfaceFactory::instance().create(className, ifaceName);
      ifaces_map.insert(std::pair<std::string, T*>(ifaceName, iface));
      return iface;
    }

    template<class C>
    void regist(std::string ifaceName){
      IfaceFactory::instance().regist<C>(ifaceName);
    }
    // for test
    string getName(){return name;};
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};

  private:
    friend struct CreateUsingNew<InterfaceMgr<T> >;
    InterfaceMgr();

    std::map<std::string, T*> ifaces_map;
    LibraryMgr* libMgr;
    typedef SingletonHolder<DynamicFactory<T> > IfaceFactory;
};

typedef SingletonHolder<InterfaceMgr<IInterface> > IfaceMgr;
static struct CreateNewMgr{
  CreateNewMgr(){
     typedef CreateUsingNew<InterfaceMgr<IInterface> > CreateNewInterfaceMgr;
     CreateNewInterfaceMgr::Create();
  }
} createNewMgr;


#endif  // IINTERFACEMGR_H
