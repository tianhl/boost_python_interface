#include "../inc/InterfaceMgr.h"
#include "../app/ImpInterface.h"
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>

template<class T>
InterfaceMgr<T>::InterfaceMgr():IInterface("IfaceMgr"){
   libMgr  = LibMgr::ptr();
   ifaces_map.insert(std::pair<std::string, T*>(this->getName(), this));
   ifaces_map.insert(std::pair<std::string, T*>(libMgr->getName(), dynamic_cast<T*>(libMgr)));
}

//template<class T>
//T* InterfaceMgr<T>::getInterface(const string& ifaceName){
//  IFACES_MAP::iterator it_iface  = ifaces_map.find(ifaceName);
//  return it_iface != ifaces_map.end()?dynamic_cast<T*>(it_iface->second):NULL;
//};
