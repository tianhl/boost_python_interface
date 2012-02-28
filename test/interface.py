#!/usr/bin/env python
from libInterface import *
#aMgr = InterfaceMgr('interfaceMgr')
aMgr = InterfaceMgr()
aImp = aMgr.create('ImpInterface','callbymgr0')
bImp = aMgr.create('Imp2Interface','callbymgr2')

tmpImp = aMgr.getInterface('callbymgr')

print aMgr.getName(), "'s point is ", aMgr, ", and its type is ", aMgr.getType()   
print aImp.getName(), "'s point is ", aImp, ", and its type is ", aImp.getType()
print bImp.getName(), "'s point is ", bImp, ", and its type is ", bImp.getType()
if tmpImp is None :
  print 'called by mgr faiture'
else:
  print tmpImp.getName(), "'s point is ", tmpImp, ", and its type is ", tmpImp.getType(), ', this point is called by mgr'


print aMgr.sayHello()

