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

/**
 * A CoefDiffusion kernel with a controllable coef.
 */
class CoefDiffusionTwo : public Kernel
{
public:

  /**
   * Constructor
   *
   * @param parameters The parameters object with the controllable coef.
   */
  CoefDiffusionTwo(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  /// declared as a reference so it can be controlled.
  const Real & _coef;
};

#endif //COEFDIFFUSIONTWO_H
