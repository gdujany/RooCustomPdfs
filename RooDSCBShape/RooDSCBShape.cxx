/*****************************************************************************
* Project: RooFit                                                           *
*                                                                           *
* This code was autogenerated by RooClassFactory                            *
*                                                                           *
* Code massaged by Giulio Dujany - University of Manchester                 *
*****************************************************************************/

// Your description goes here...

#include "Riostream.h"

#include "RooDSCBShape.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include <math.h>
#include "TMath.h"

ClassImp(RooDSCBShape)

RooDSCBShape::RooDSCBShape(const char *name, const char *title,
  RooAbsReal& _x,
  RooAbsReal& _mu,
  RooAbsReal& _sig,
  RooAbsReal& _a1,
  RooAbsReal& _n1,
  RooAbsReal& _a2,
  RooAbsReal& _n2) :
  RooAbsPdf(name,title),
  x("x","x",this,_x),
  mu("mu","mu",this,_mu),
  sig("sig","sig",this,_sig),
  a1("a1","a1",this,_a1), //a1 must be > 0
  n1("n1","n1",this,_n1),
  a2("a2","a2",this,_a2), //a2 must be > 0
  n2("n2","n2",this,_n2)
  {
  }


  RooDSCBShape::RooDSCBShape(const RooDSCBShape& other, const char* name) :
  RooAbsPdf(other,name),
  x("x",this,other.x),
  mu("mu",this,other.mu),
  sig("sig",this,other.sig),
  a1("a1",this,other.a1),
  n1("n1",this,other.n1),
  a2("a2",this,other.a2),
  n2("n2",this,other.n2)
  {
  }



  Double_t RooDSCBShape::evaluate() const
  {
    double u   = (x-mu)/sig;
    double A1  = TMath::Power(n1/TMath::Abs(a1),n1)*TMath::Exp(-a1*a1/2);
    double A2  = TMath::Power(n2/TMath::Abs(a2),n2)*TMath::Exp(-a2*a2/2);
    double B1  = n1/a1 - a1;
    double B2  = n2/a2 - a2;

    double result(1);
    if      (u<-TMath::Abs(a1)) result *= A1*TMath::Power(B1-u,-n1);
    else if (u<TMath::Abs(a2))  result *= TMath::Exp(-u*u/2);
    else                        result *= A2*TMath::Power(B2+u,-n2);
    return result;
  }


  Int_t RooDSCBShape::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char*) const
  {
    if (matchArgs(allVars,analVars,x)) return 1 ;
    return 0 ;
  }

  Double_t RooDSCBShape::analyticalIntegral(Int_t code, const char* r) const
  {
    double umin = (x.min(r) - mu) / sig;
    double umax = (x.max(r) - mu) / sig;
    R__ASSERT(code==1);

    double integral = 0.;

    integral += IntPwLw(TMath::Max(-umax, TMath::Abs(a1)), TMath::Max(-umin, TMath::Abs(a1)), a1, n1);
    integral += IntGaus(TMath::Max(umin, -TMath::Abs(a1)), TMath::Min(umax, TMath::Abs(a2)));
    integral += IntPwLw(TMath::Max(umin, TMath::Abs(a2)), TMath::Max(umax, TMath::Abs(a2)), a2, n1);

    return sig * integral;
  }


  double RooDSCBShape::IntGaus(double x0, double x1) const
  {
    static const double rootPiBy2 = TMath::Sqrt(TMath::PiOver2());

    if (x0 >= x1) return 0; // needed in case umin > a2

    // N.B. Erf is integral from 0
    if (x0*x1<0) // they are at different side of zero
    {
      return rootPiBy2 * ( TMath::Erf(TMath::Abs(x1) / TMath::Sqrt2()) + TMath::Erf(TMath::Abs(x0) / TMath::Sqrt2()) );
    }
    else //They are at the same side of zero
    {
      return rootPiBy2 * ( TMath::Erf(TMath::Abs(x1) / TMath::Sqrt2()) - TMath::Erf(TMath::Abs(x0) / TMath::Sqrt2()) );
    }

  }

  double RooDSCBShape::IntPwLw(double x0, double x1, double alpha, double n) const
  {

    if (x0 == x1) return 0; // already implicit below but so it's clear

    bool useLog = false;
    if(fabs(n - 1.0) < 1.0e-05)
    useLog = true;

    double A  = TMath::Power(n/TMath::Abs(alpha),n)*TMath::Exp(-alpha*alpha/2);
    double B  = n/TMath::Abs(alpha) - TMath::Abs(alpha);

    double result = 0.;
    if(useLog)
    {
      result = A * ( TMath::Log(B - x1) - TMath::Log(B - x0));
    }
    else
    {
      result = A / (1. - n) * ( TMath::Power(B + x1, 1. - n) - TMath::Power(B + x0, 1. - n) );
    }
    return result;
  }
