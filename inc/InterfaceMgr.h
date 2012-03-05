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

//class InterfaceFactory:public  DynamicFactory<IInterface>{
//  public:
//    IInterface* create(const std::string& className, const std::string& ifaceName){
//      return DynamicFactory<IInterface>::create(className, ifaceName);
//    }
//
//};
//typedef SingletonHolder<InterfaceFactory> IfaceFactory;
typedef SingletonHolder<DynamicFactory<IInterface> > IfaceFactory;

class InterfaceMgr:public IInterface{
  public:

    IInterface* getInterface(const std::string& ifaceName);

    IInterface* create(const std::string& className, const std::string& ifaceName){
      IInterface* iface = IfaceFactory::instance().create(className, ifaceName);
      ifaces_map.insert(IFACES_MAP::value_type(ifaceName, iface));
      return iface;
    }
    // for test
    string getName(){return name;};
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};

  private:
    friend struct CreateUsingNew<InterfaceMgr>;
    ///Private Constructor
    InterfaceMgr();
    //// Private copy constructor - NO COPY ALLOWED
    //InterfaceMgr(const InterfaceMgr&);
    ///// Private assignment operator - NO ASSIGNMENT ALLOWED
    //InterfaceMgr& operator = (const InterfaceMgr&);
    /////Private Destructor
    //virtual ~InterfaceMgr();

    //std::map<std::string, IInterface*> ifaces_map;
    typedef std::map<std::string, IInterface*> IFACES_MAP;
    IFACES_MAP ifaces_map;
    LibraryMgr* libMgr;

//    class InterfaceFactory:public DynamicFactory<IInterface>{
//    }

};

typedef SingletonHolder<InterfaceMgr> IfaceMgr;


#endif  // IINTERFACEMGR_H
