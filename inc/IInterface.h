#ifndef IINTERFACE_H
#define IINTERFACE_H
#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

class IInterface
{
  public:
    IInterface(string n):name(n){};
    virtual ~IInterface(){};
    virtual string getName() = 0;
    virtual string getType(){return typeid(this).name();}


    string name;
};

using namespace boost::python;

struct IInterface_callback :public IInterface, wrapper<IInterface>
{
  public:
    IInterface_callback(string n) :  IInterface(n) {}  // boost::noncopyable  only default construtor
    string getName() { return this->get_override("getName")(); }   // for pure virtual function
    string getType(){                                                          // for virtual function
      if (override getType = this->get_override("getType")) return getType();
      else return IInterface::getType();
    }
    string default_getType() { return this->IInterface::getType(); }
};

// example:
// class PyAlgorithmCallback : public PyAlgorithmBase{
// public:
//   PyAlgorithmCallback(PyObject *self): PyAlgorithmBase(), m_self(self);
//   int version() const ;
// private:
//   PyObject *m_self;
// }
// int PyAlgorithmCallback::version() const
// {
//   return PyCall_NoArg<const int>::dispatch(m_self, "version");
// }
template<typename ResultType>
struct PyCall_NoArg {
  static ResultType dispatch(PyObject *object, const std::string & func_name) {
      return boost::python::call_method<ResultType>(object, func_name.c_str());
  }
};


#endif  // IINTERFACE_H
