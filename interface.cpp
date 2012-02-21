#include <boost/python/module.hpp>
#include <boost/python/class.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/call.hpp>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::python;
using namespace std;

class IInterface
{
  public:
    IInterface(string n):name(n){};
    virtual ~IInterface(){};
    virtual string getName() = 0;
    string name;
};

class ImpInterface :public IInterface{
  public:
    ImpInterface(string n):IInterface(n){};
    virtual string getName(){return name+"_Imp";};
};

class InterfaceMgr{
  public:
    IInterface* create(string name){ 
      return dynamic_cast<IInterface*>(new  ImpInterface(name));
    };
};

struct IInterface_callback :public IInterface, wrapper<IInterface>
{
  public:
    IInterface_callback(string n) :  IInterface(n) {}  // boost::noncopyable  only default construtor
    string getName() { return this->get_override("getName")(); }
};

class InterfaceMgr_callback:public InterfaceMgr{
  public:
    InterfaceMgr_callback(PyObject *p) : self(p) {}  //  default construtor
    IInterface* create(string name){ return boost::python::call_method<IInterface*>(self, "create", name); }
    static IInterface*  default_create(InterfaceMgr& self_, string name) { return self_.InterfaceMgr::create(name);}  // necessary
  private:
    PyObject *self;
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(FM_createOverloader, InterfaceMgr::create, 1, 1)

BOOST_PYTHON_MODULE_INIT(interface)
{
  class_<IInterface_callback,boost::noncopyable>("IInterface", init<string>())
    .def("getName", pure_virtual(&IInterface::getName))
    ;

  class_<InterfaceMgr, boost::noncopyable, boost::shared_ptr<InterfaceMgr_callback> >("InterfaceMgr")
    .def("create",  &InterfaceMgr::create, FM_createOverloader()[return_internal_reference<>()])
    ;
}
