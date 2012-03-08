#include "../alg/ImpInterface.h"

static Register impinterface_regist;
string ImpInterface::getName(){return name;}; 
string ImpInterface::getType(){return typeid(this).name();};
string Imp2Interface::getType(){return typeid(this).name();};
