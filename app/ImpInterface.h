#ifndef IMPINTERFACE_H
#define IMPINTERFACE_H
#include "../inc/IInterface.h"
#include "../inc/InterfaceMgr.h"
using namespace std;


class ImpInterface :public IInterface{
  public:
    ImpInterface():IInterface("ImpInterface"){ };
    ImpInterface(string n):IInterface(n){ };
    virtual string getName();
    virtual string getType();
};

class Imp2Interface :public ImpInterface{
  public:
    Imp2Interface(string n):ImpInterface(n){};
    virtual string getType();
};

// it can defined in .cpp file without static
// or defined in .h file with static
struct Register{
  Register(){
    IfaceFactory::instance().regist<ImpInterface>("ImpInterface");
    IfaceFactory::instance().regist<Imp2Interface>("Imp2Interface");
  }
};
static Register impinterface_regist;
#endif  // IMPINTERFACE_H

