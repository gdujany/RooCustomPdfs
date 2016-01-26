#!/usr/bin/env python

import ROOT as r

<<<<<<< HEAD
r.gSystem.Load('../RooDSCBShape_cxx')
=======
r.gSystem.Load('RooDSCBShape_cxx')
>>>>>>> 644b902ede29b42298d39cc2258ac7e5cb1b4300
r.gSystem.Load('RooDSCBShapeOld_cxx')

w = r.RooWorkspace()

<<<<<<< HEAD
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
=======
# w.factory('x[-10,-2]') # ok
# w.factory('x[2,10]')   # ok
# w.factory('x[-2,2]')     # ok
w.factory('x[-4,7]')


dscb_str = '''(x,
  #mu[3],
  #sigma[3],
>>>>>>> 644b902ede29b42298d39cc2258ac7e5cb1b4300
  #alpha1[2], n1[2],
  #alpha2[2], n2[2]
  )'''

w.factory('RooDSCBShape::analitic'+dscb_str)
w.factory('RooDSCBShapeOld::numeric'+dscb_str)


print w.pdf('analitic').createIntegral(r.RooArgSet(w.var('x'))).getVal()
print w.pdf('numeric').createIntegral(r.RooArgSet(w.var('x'))).getVal()
