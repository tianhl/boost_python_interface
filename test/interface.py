#!/usr/bin/env python
from Interface import *
#aMgr = InterfaceMgr('interfaceMgr')
aMgr = InterfaceMgr()
aImp = aMgr.create('ImpInterface','callbymgr0')
bImp = aMgr.create('Imp2Interface','callbymgr2')

print aMgr.getName(), "'s point is ", aMgr, ", and its type is ", aMgr.getType()   
print aImp.getName(), "'s point is ", aImp, ", and its type is ", aImp.getType()
print bImp.getName(), "'s point is ", bImp, ", and its type is ", bImp.getType()


print aMgr.sayHello()

