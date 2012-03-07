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
#include "../inc/DynamicManager.h"

//#include "../app/ImpInterface.h"

using namespace std;

static struct CreateNewMgr{
  CreateNewMgr(){
     typedef CreateUsingNew<DynamicManager<IInterface> > CreateNewInterfaceMgr;
     std::cout << "---------------------" << std::endl;
     CreateNewInterfaceMgr::Create();
  }
} createNewMgr;


class InterfaceManager:public IInterface, public DynamicManager<IInterface>{
  public:
    InterfaceManager();
    // for test
    string getName(){return name;};
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};
  private:
    LibraryMgr* libMgr;
};

typedef SingletonHolder<InterfaceManager > IfaceMgr;

#endif  // IINTERFACEMGR_H
