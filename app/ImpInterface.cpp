#include "../app/ImpInterface.h"

string ImpInterface::getName(){return name;}; 
string ImpInterface::getType(){return typeid(this).name();};
string Imp2Interface::getType(){return typeid(this).name();};

//struct Register{
//  Register(){
//    IfaceFactory::instance().regist<ImpInterface>("ImpInterface");
//    IfaceFactory::instance().regist<Imp2Interface>("Imp2Interface");
//  }
//} impinterface_regist;
