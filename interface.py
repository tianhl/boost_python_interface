#!/usr/bin/env python
from interface import *
aMgr = InterfaceMgr('interfaceMgr')
#aMgr = InterfaceMgr()
aImp = aMgr.create('callbymgr')
bImp = aMgr.create('callbymgr_again')

print aMgr.getName(), "'s point is ", aMgr, ", and its type is ", aMgr.getType()   
print aImp.getName(), "'s point is ", aImp, ", and its type is ", aImp.getType()
print bImp.getName(), "'s point is ", bImp, ", and its type is ", bImp.getType()

