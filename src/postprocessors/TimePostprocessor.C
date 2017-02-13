#include "TimePostprocessor.h"

template<>
InputParameters validParams<TimePostprocessor>()
{
  InputParameters params = validParams<GeneralPostprocessor>();

  return params;
}

TimePostprocessor::TimePostprocessor(const InputParameters & parameters) :
    GeneralPostprocessor(parameters)
{
}

TimePostprocessor::~TimePostprocessor()
{
}

void
TimePostprocessor::initialize()
{
}

void
TimePostprocessor::execute()
{
}

Real
TimePostprocessor::getValue()
{
  return _t;
}
