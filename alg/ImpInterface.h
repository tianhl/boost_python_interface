#ifndef IMPINTERFACE_H
#define IMPINTERFACE_H
#include "../inc/IInterface.h"
#include "../inc/InterfaceManager.h"
using namespace std;


class ImpInterface :public IInterface{
  public:
    ImpInterface():IInterface("ImpInterface"){};//id = make_pair(name, typeid(this).name()); };
    ImpInterface(string n):IInterface(n){ };
    virtual string getName();
    virtual string getType();
    
};

class Imp2Interface :public ImpInterface{
  public:
    Imp2Interface(string n):ImpInterface(n){};
    virtual string getType();
};

struct Register{
  Register(){
    IfaceMgr::instance().regist<ImpInterface>("ImpInterface");
    IfaceMgr::instance().regist<Imp2Interface>("Imp2Interface");
  }
};
#endif  // IMPINTERFACE_H

