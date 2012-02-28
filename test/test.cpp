#include "../inc/IInterface.h"
#include "../inc/InterfaceMgr.h"
#include <iostream>
using namespace std;

int main(void)
{
  //InterfaceMgr* pMgr = new InterfaceMgr();
  InterfaceMgr& rMgr = IfaceMgr::Instance();
  IInterface* pImp0  = rMgr.create("ImpInterface", "callatcpp");
  IInterface* pImp1 = rMgr.getInterface("callatcpp");
  
  std::cout << pImp0->getName() << "'s point is " << pImp0 << ", and its type is " << pImp0->getType() << std::endl;
  std::cout << rMgr.getName() <<  "'s type is " << rMgr.getType() << std::endl;
  std::cout << pImp1->getName() << "'s point is " << pImp1 << ", and its type is " << pImp1->getType() << std::endl;

  return 0;
}
