#ifndef DYNAMICMANAGER_H
#define DYNAMICMANAGER_H

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

#include "../inc/DynamicFactory.h"

using namespace std;


template<class T>
class DynamicManager{
  public:

    DynamicManager();
    T* getInterface(const std::string& ifaceName){
      // why map<std::string, T*>::iterator cannot work?
      return ifaces_map.find(ifaceName) != ifaces_map.end() ?  dynamic_cast<T*>(ifaces_map.find(ifaceName)->second)  : NULL ;
    };

    T* create(const std::string& className, const std::string& ifaceName){
      T* iface = IfaceFactory::instance().create(className, ifaceName);
      ifaces_map.insert(std::pair<std::string, T*>(ifaceName, iface));
      return iface;
    }

    template<class C>
    void regist(std::string ifaceName){
      IfaceFactory::instance().regist<C>(ifaceName);
    }

    friend struct CreateUsingNew<DynamicManager<T> >;
    std::map<std::string, T*> ifaces_map;
  private:

    typedef SingletonHolder<DynamicFactory<T> > IfaceFactory;
};


#endif  // DYNAMICMANAGER_H
