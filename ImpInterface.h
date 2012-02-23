#ifndef IMPINTERFACE_H
#define IMPINTERFACE_H
#include "IInterface.h"
using namespace std;


class ImpInterface :public IInterface{
  public:
    ImpInterface(string n):IInterface(n){};
    virtual string getName();
    virtual string getType(){return typeid(this).name();};
};

class Imp2Interface :public ImpInterface{
  public:
    Imp2Interface(string n):ImpInterface(n){};
};

#endif  // IMPINTERFACE_H
                                                                                                                                                             
