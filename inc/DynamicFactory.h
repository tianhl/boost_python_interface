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
  virtual boost::shared_ptr<Base> createInstance() const = 0;
  virtual Base* createUnwrappedInstance() const = 0;

private:
  AbstractInstantiator(const AbstractInstantiator&);
  AbstractInstantiator& operator = (const AbstractInstantiator&);
};

template <class C, class Base>
class Instantiator: public AbstractInstantiator<Base> {
public:
  Instantiator() { }
  virtual ~Instantiator() { }
  boost::shared_ptr<Base> createInstance() const { return boost::shared_ptr<Base>(new C); }
};

template <class Base>
class DynamicFactory
{
  public:
    typedef AbstractInstantiator<Base> AbstractFactory;

    virtual ~DynamicFactory() {
      for (typename FactoryMap::iterator it = _map.begin(); it != _map.end(); ++it) {delete it->second;}
    }

    virtual boost::shared_ptr<Base> create(const std::string& className) const {   
      typename FactoryMap::const_iterator it = _map.find(className);
      if (it != _map.end()) return it->second->createInstance();
      else throw std::runtime_error("DynamicFactory:"+ className + " is not registered.\n");
    }

    template <class C> 
    void regist(const std::string& className) { regist(className, new Instantiator<C, Base>); }


    void regist(const std::string& className, AbstractFactory* pAbstractFactory) {
      typename FactoryMap::iterator it = _map.find(className);
      (!className.empty() && it == _map.end()) ?  _map[className] = pAbstractFactory : delete pAbstractFactory;
    }

    void unregist(const std::string& className) {
      typename FactoryMap::iterator it = _map.find(className);
      if (!className.empty() && it != _map.end()) {
	delete it->second;
	_map.erase(it);
      }
    }

    bool exists(const std::string& className) const { return _map.find(className) != _map.end(); }

    virtual const std::vector<std::string> getKeys() const {
      std::vector<std::string> names;
      names.reserve(_map.size());

      typename FactoryMap::const_iterator iter = _map.begin();
      for (; iter != _map.end(); ++iter) { names.push_back(iter->first); }

      return names;
    }


  protected:
    DynamicFactory() { }  

  private:
    DynamicFactory(const DynamicFactory&);
    DynamicFactory& operator = (const DynamicFactory&);

    typedef std::map<std::string, AbstractFactory*> FactoryMap;
    FactoryMap _map;
};

#endif /*DYNAMICFACTORY_H*/
