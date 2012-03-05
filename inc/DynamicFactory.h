#ifndef DYNAMICFACTORY_H
#define DYNAMICFACTORY_H

//----------------------------------------------------------------------
// Includes
//----------------------------------------------------------------------

// Boost
#include <boost/shared_ptr.hpp>

// std
#include <map>
#include <iostream>
#include <vector>


template <class Base>
class AbstractInstantiator {
public:
  AbstractInstantiator() { }
  virtual ~AbstractInstantiator() { }
  virtual Base* createInstance(const std::string& instanceName) const = 0;
};

template <class C, class Base>
class Instantiator: public AbstractInstantiator<Base> {
public:
  Instantiator() { }
  virtual ~Instantiator() { }
  Base* createInstance(const std::string& instanceName) const { return dynamic_cast<Base*>(new C(instanceName)); }
};

template <class Base>
class DynamicFactory
{
  public:
    typedef AbstractInstantiator<Base> AbstractFactory;

    virtual ~DynamicFactory() {
      for (typename FactoryMap::iterator it = _map.begin(); it != _map.end(); ++it) {delete it->second;}
    }

    virtual Base* create(const std::string& className, const std::string& instanceName) const {   
      typename FactoryMap::const_iterator it = _map.find(className);
      if (it != _map.end()) return it->second->createInstance(instanceName);
      else throw std::runtime_error("DynamicFactory:"+ className + " is not registered.\n");
    }

    template <class C> 
    void regist(const std::string& className) { regist(className, new Instantiator<C, Base>); }

    void regist(const std::string& className, AbstractFactory* pAbstractFactory)
    {
      typename FactoryMap::iterator it = _map.find(className);
      if (!className.empty() && it == _map.end())
      {
	_map[className] = pAbstractFactory;
      }
      else
      {
	delete pAbstractFactory;
	throw std::runtime_error(className + " is already registered.\n");
      }
    }

    DynamicFactory() { }  
    DynamicFactory(const DynamicFactory&);
    DynamicFactory& operator = (const DynamicFactory&);

  private:
    typedef std::map<std::string, AbstractFactory*> FactoryMap;
    FactoryMap _map;
};

#endif /*DYNAMICFACTORY_H*/
