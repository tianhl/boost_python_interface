#include "../inc/IInterface.h"
#include "../inc/InterfaceMgr.h"
#include "../inc/LibraryMgr.h"
#include "../app/ImpInterface.h"
#include <iostream>
using namespace std;

int main(void)
{
  //InterfaceMgr* pMgr = new InterfaceMgr();
  InterfaceMgr* aIfaceMgr  = IfaceMgr::ptr();
  LibraryMgr* aLibMgr = static_cast<LibraryMgr*>(aIfaceMgr->getInterface("LibMgr"));
  std::cout << "aLibMgr name: " << aLibMgr->getName() << std::endl;
  std::cout << "aLibMgr type: " << typeid(aLibMgr) << std::endl;


  //DynamicFactory<IInterface>::regist<ImpInterface>("ImpInterface");

  IInterface* pImp1 = aIfaceMgr->create("ImpInterface", "ImpInterface");
  IInterface* pImp0 = aIfaceMgr->getInterface("ImpInterface");
  //
  std::cout << pImp0->getName() << "'s point is " << pImp0 << ", and its type is " << pImp0->getType() << std::endl;
  //std::cout << rMgr.getName() <<  "'s type is " << rMgr.getType() << std::endl;
  std::cout << pImp1->getName() << "'s point is " << pImp1 << ", and its type is " << pImp1->getType() << std::endl;

  return 0;
}
