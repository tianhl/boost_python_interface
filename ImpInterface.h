#ifndef IMPINTERFACE_H
#define IMPINTERFACE_H
#include "IInterface.h"
using namespace std;


class ImpInterface :public IInterface{
  public:
    ImpInterface(string n):IInterface(n){};
    virtual string getName();
};

#endif  // IMPINTERFACE_H
                                                                                                                                                             
