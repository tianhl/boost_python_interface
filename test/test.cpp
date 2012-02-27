#include "../inc/IInterface.h"
#include "../inc/InterfaceMgr.h"
#include <iostream>
using namespace std;

int main(void)
{
  InterfaceMgr* pMgr = new InterfaceMgr();
  IInterface* pImp0  = pMgr->create("ImpInterface", "callatcpp");
  
  std::cout << pImp0->getName() << "'s point is " << pImp0 << ", and its type is " << pImp0->getType() << std::endl;

  return 0;
}
