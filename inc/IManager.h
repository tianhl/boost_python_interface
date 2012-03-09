#ifndef IMANAGER_H
#define IMANAGER_H

// std
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "../inc/IInterface.h"

using namespace std;

template <class T>
class IManager:public IInterface{
  public:
    IManager():IInterface("IManager"){};
    IManager(std::string n):IInterface(n){};
    virtual T* getInterface(const std::string& ifaceName)=0;
    virtual T* createInterface(const std::string& className, const std::string& ifaceName)=0;
    virtual const std::vector<std::string> getKeys()=0;

    template<class C>
    virtual void registFactory(std::string className)=0

};

#endif  // IMANAGER_H
