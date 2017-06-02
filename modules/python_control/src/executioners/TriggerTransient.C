#include "TriggerTransient.h"
#include "PythonControl.h"

template<>
InputParameters validParams<TriggerTransient>()
{
  InputParameters pars = validParams<Transient>();

  return pars;
}

TriggerTransient::TriggerTransient(const InputParameters & params) :
    Transient(params)
{
}

bool
TriggerTransient::keepGoing()
{
  bool transient_response = Transient::keepGoing();
  bool python_response = PythonControl::keepGoing();

  return transient_response && python_response;
}
