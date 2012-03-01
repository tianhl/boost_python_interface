#include "../inc/InterfaceMgr.h"

InterfaceMgr::InterfaceMgr():IInterface("IfaceMgr"){
   libMgr  = &LibMgr::Instance();
   ifaces_map.insert(std::map<std::string, IInterface*>::value_type(this->getName(), this));
   ifaces_map.insert(std::map<std::string, IInterface*>::value_type(libMgr->getName(), dynamic_cast<IInterface*>(libMgr)));
}

IInterface* InterfaceMgr::create(const string& ifaceType, const string& ifaceName){
}

IInterface* InterfaceMgr::getInterface(const string& ifaceName){
  std::map<std::string, IInterface*>::iterator it_iface;
  it_iface = ifaces_map.find(ifaceName);
  return (  (it_iface != ifaces_map.end()) ? dynamic_cast<IInterface*>(it_iface->second)  : NULL );
}
