#include "../inc/InterfaceMgr.h"
#include "../app/ImpInterface.h"
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>

InterfaceMgr::InterfaceMgr():IInterface("IfaceMgr"){
   libMgr  = LibMgr::ptr();
   ifaces_map.insert(IFACES_MAP::value_type(this->getName(), this));
   ifaces_map.insert(IFACES_MAP::value_type(libMgr->getName(), dynamic_cast<IInterface*>(libMgr)));

}

IInterface* InterfaceMgr::getInterface(const string& ifaceName){
  IFACES_MAP::iterator it_iface = ifaces_map.find(ifaceName);
  return it_iface != ifaces_map.end()?dynamic_cast<IInterface*>(it_iface->second):NULL;
}
