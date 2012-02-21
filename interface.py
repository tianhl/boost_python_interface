from interface import *
aMgr = InterfaceMgr()
aImp = aMgr.create('callbymgr')
#aImp.name='callbymgr'
print aImp
print aImp.getName()
