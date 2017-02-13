/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#ifndef COEFDIFFUSIONTWO_H
#define COEFDIFFUSIONTWO_H

#include "Kernel.h"

//Forward Declarations
class CoefDiffusionTwo;

template<>
InputParameters validParams<CoefDiffusionTwo>();

class CoefDiffusionTwo : public Kernel
{
public:

  CoefDiffusionTwo(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _coef;
};

#endif //COEFDIFFUSIONTWO_H
