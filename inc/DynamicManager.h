#ifndef DYNAMICMANAGER_H
#define DYNAMICMANAGER_H

// std
#include <string>
#include <map>
#include <algorithm>

using namespace std;
template<class T>
class DynamicManager
{
  public:
    virtual T* getInterface(const std::string& ifaceName){
      return  _map.find(ifaceName) != _map.end()?dynamic_cast<T*>(_map.find(ifaceName)->second):
	throw std::runtime_error("DynamicManager:"+ifaceName+" is not created.\n");
    }
    virtual T* create(const std::string& className, const std::string& ifaceName)=0;
    void insert(const std::string& ifaceName, T* iface){
      typename InterfaceMap::iterator it = _map.find(ifaceName);
      if(!ifaceName.empty() && it == _map.end()){
      _map.insert(std::pair<std::string, T*>(ifaceName, iface));
      }
      else{
	std::cout << ifaceName << " is already existed." << std::endl;
      }
    }
  private:
    typedef std::map<std::string, T*> InterfaceMap;
    InterfaceMap _map;
};


#endif  // DYNAMICMANAGER_H
