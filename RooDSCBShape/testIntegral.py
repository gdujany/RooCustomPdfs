#!/usr/bin/env python

import ROOT as r


r.gSystem.Load('../RooDSCBShape_cxx')
r.gSystem.Load('RooDSCBShapeOld_cxx')

w = r.RooWorkspace()

#w.factory('x[-10,-2]') # ok
# w.factory('x[2,10]')   # ok
# w.factory('x[-2,2]')     # ok
#w.factory('x[-4,7]')
#w.factory('x[-5,-2]') # ok
w.factory('x[-10,-1]') # ok
#w.factory('x[-1.9,-1]') # ok

dscb_str = '''(x,
  #mu[0],
  #sigma[1],
  #alpha1[2], n1[2],
  #alpha2[2], n2[2]
  )'''

w.factory('RooDSCBShape::analitic'+dscb_str)
w.factory('RooDSCBShapeOld::numeric'+dscb_str)


print w.pdf('analitic').createIntegral(r.RooArgSet(w.var('x'))).getVal()
print w.pdf('numeric').createIntegral(r.RooArgSet(w.var('x'))).getVal()
