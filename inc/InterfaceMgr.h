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
class DynamicManager
{
  public:
    virtual T* getInterface(const std::string& ifaceName){
      return  _map.find(ifaceName) != _map.end()?dynamic_cast<T*>(_map.find(ifaceName)->second):NULL;
    }
    virtual T* create(const std::string& className, const std::string& ifaceName)=0;
    void insert(const std::string& ifaceName, T* iface){
      _map.insert(std::pair<std::string, T*>(ifaceName, iface));
    }
  private:
    typedef std::map<std::string, T*> InterfaceMap;
    InterfaceMap _map;
};

class InterfaceManager:public IInterface{
  public:
    IInterface* getInterface(const std::string& ifaceName){
      return IfaceMgrImp::instance().getInterface(ifaceName);
    }
    IInterface* create(const std::string& className, const std::string& ifaceName){
      return IfaceMgrImp::instance().create(className, ifaceName);
    }
    std::string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};

    template<class C>
    void regist(std::string ifaceName){
      InterfaceFactory::instance().regist<C>(ifaceName);
    };


  private:
    friend struct CreateUsingNew<InterfaceManager>;
    InterfaceManager();

    class InterfaceManagerImp: public DynamicManager<IInterface> {
      public:
	virtual IInterface* create(const std::string& className, const std::string& ifaceName){
	  IInterface* iface = InterfaceFactory::instance().create(className, ifaceName);
	  insert(ifaceName, iface);
	  return iface;
	}
    };

    typedef SingletonHolder<InterfaceManagerImp > IfaceMgrImp;
    typedef SingletonHolder<DynamicFactory<IInterface> > InterfaceFactory;

};

typedef SingletonHolder<InterfaceManager> IfaceMgr;

//class InterfaceMgr:public IInterface{
//  public:
//
//    IInterface* getInterface(const std::string& ifaceName);
//
//    IInterface* create(const std::string& className, const std::string& ifaceName){
//      IInterface* iface = IfaceFactory::instance().create(className, ifaceName);
//      ifaces_map.insert(IFACES_MAP::value_type(ifaceName, iface));
//      return iface;
//    };
//    // for test
//    string getName(){return name;};
//    virtual string getType(){return typeid(this).name();};
//    string sayHello(){return getName() + " say hello ";};
//
//    template<class C>
//    void regist(std::string ifaceName){
//      IfaceFactory::instance().regist<C>(ifaceName);
//    };
//
//  private:
//    friend struct CreateUsingNew<InterfaceMgr>;
//    ///Private Constructor
//    InterfaceMgr();
//    //// Private copy constructor - NO COPY ALLOWED
//    //InterfaceMgr(const InterfaceMgr&);
//    ///// Private assignment operator - NO ASSIGNMENT ALLOWED
//    //InterfaceMgr& operator = (const InterfaceMgr&);
//    /////Private Destructor
//    //virtual ~InterfaceMgr();
//
//    //std::map<std::string, IInterface*> ifaces_map;
//    typedef std::map<std::string, IInterface*> IFACES_MAP;
//    IFACES_MAP ifaces_map;
//    LibraryMgr* libMgr;
//
//    typedef SingletonHolder<DynamicFactory<IInterface> > IfaceFactory;
//    //    class InterfaceFactory:public DynamicFactory<IInterface>{
//    //    }
//
//};
//
//
//typedef SingletonHolder<InterfaceMgr> IfaceMgr;


#endif  // IINTERFACEMGR_H
