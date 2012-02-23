#!/usr/bin/env python
from interface import *
aMgr = InterfaceMgr('interfaceMgr')
#aMgr = InterfaceMgr()
aImp = aMgr.create('callbymgr')
bImp = aMgr.create('callbymgr_again')

print aMgr.getName(), "'s point is ", aMgr   
print aImp.getName(), "'s point is ", aImp
print bImp.getName(), "'s point is ", bImp

