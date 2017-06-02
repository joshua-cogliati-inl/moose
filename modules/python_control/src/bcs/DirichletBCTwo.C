#include "DirichletBCTwo.h"

template<>
InputParameters validParams<DirichletBCTwo>()
{
  InputParameters p = validParams<DirichletBC>();
  p.declareControllable("value");
  return p;
}

DirichletBCTwo::DirichletBCTwo(const InputParameters & parameters) :
  DirichletBC(parameters)
{
}
