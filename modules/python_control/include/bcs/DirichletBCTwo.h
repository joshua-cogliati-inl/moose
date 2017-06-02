#ifndef DIRICHLETBCTWO_H
#define DIRICHLETBCTWO_H

#include "DirichletBC.h"

class DirichletBCTwo;

template<>
InputParameters validParams<DirichletBCTwo>();

/**
 * This implements a Dirichlet boundary condition that has a controllable
 * value.
 */
class DirichletBCTwo : public DirichletBC
{
public:
  /**
   * Constructor
   *
   * @param parameters The parameters object holding data for the class to use.
   */
  DirichletBCTwo(const InputParameters & parameters);

};

#endif /* DIRICHLETBCTWO_H */
