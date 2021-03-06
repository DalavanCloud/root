/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * @(#)root/roofit:$Id$
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/

/** \class RooUnblindUniform
    \ingroup Roofit

Implementation of BlindTools' offset blinding method
A RooUnblindUniform object is a real valued function
object, constructed from a blind value holder and a
set of unblinding parameters. When supplied to a PDF
in lieu of a regular parameter, the blind value holder
supplied to the unblinded objects will in a fit be minimized
to blind value corresponding to the actual minimum of the
parameter. The transformation is chosen such that the
the error on the blind parameters is identical to that
of the unblind parameter
**/

#include "RooFit.h"

#include "RooArgSet.h"
#include "RooArgSet.h"
#include "RooUnblindUniform.h"


using namespace std;

ClassImp(RooUnblindUniform);

////////////////////////////////////////////////////////////////////////////////
/// Default constructor

RooUnblindUniform::RooUnblindUniform()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor from a given RooAbsReal (to hold the blind value) and a set of blinding parameters

RooUnblindUniform::RooUnblindUniform(const char *name, const char *title,
                const char *blindString, Double_t scale, RooAbsReal& cpasym)
  : RooAbsHiddenReal(name,title),
  _value("value","Uniform blinded value",this,cpasym),
  _blindEngine(blindString,RooBlindTools::full,0.,scale)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Copy constructor

RooUnblindUniform::RooUnblindUniform(const RooUnblindUniform& other, const char* name) :
  RooAbsHiddenReal(other, name),
  _value("asym",this,other._value),
  _blindEngine(other._blindEngine)
{
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor

RooUnblindUniform::~RooUnblindUniform()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Evaluate RooBlindTools unhide-offset method on blind value

Double_t RooUnblindUniform::evaluate() const
{
  return _blindEngine.UnHideUniform(_value);
}
