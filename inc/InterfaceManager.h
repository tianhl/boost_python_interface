#ifndef INTERFACEMGR_H
#define INTERFACEMGR_H


#include "../inc/IManager.h"
#include "../inc/DynamicFactory.h"
#include "../inc/DynamicManager.h"
#include "../inc/SingletionHolder.h"

using namespace std;

class InterfaceManager:public IManager<IInterface>{
  public:
    IInterface* getInterface(const std::string& ifaceName){
      IInterface* iface = IfaceMgrImp::instance().getInterface(ifaceName);
      if (iface != NULL) return iface;
      //else create(ifaceName, ifaceName);
    }
    IInterface* createInterface(const std::string& className, const std::string& ifaceName){
      return IfaceMgrImp::instance().create(className, ifaceName);
    }
    virtual const std::vector<std::string> getKeys(){
      return IfaceMgrImp::instance().getKeys();
    }

    std::string getName(){return name;}
    virtual string getType(){return typeid(this).name();};
    string sayHello(){return getName() + " say hello ";};

    template<class C>
    void registFactory(std::string ifaceName){
      InterfaceFactory::instance().regist<C>(ifaceName);
    };



  private:
    friend struct CreateUsingNew<InterfaceManager>;
    InterfaceManager():IInterface("IfaceMgr"){};

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

#endif  // IINTERFACEMGR_H
