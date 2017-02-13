#ifndef DIRICHLETBCTWO_H
#define DIRICHLETBCTWO_H

#include "DirichletBC.h"

class DirichletBCTwo;

template<>
InputParameters validParams<DirichletBCTwo>();

class DirichletBCTwo : public DirichletBC
{
public:
  DirichletBCTwo(const InputParameters & parameters);

};

#endif /* DIRICHLETBCTWO_H */
