#include "PythonControl.h"

template<>
InputParameters validParams<PythonControl>()
{
  InputParameters params = validParams<Control>();
  params.addRequiredParam<std::string>("controlled_vars", "List of variables to control");
  params.addRequiredParam<std::string>("postprocessor_vars", "List of Postprocessor variables available to the python program");
  params.addRequiredParam<std::string>("python_file", "Python File to load");

  return params;
}

PythonControl::PythonControl(const InputParameters & parameters) :
    Control(parameters)
{
  MooseUtils::tokenize(getParam<std::string>("controlled_vars"), controlled_vars, 1, " ");
  MooseUtils::tokenize(getParam<std::string>("postprocessor_vars"), postprocessor_vars, 1, " ");
  
}

void
PythonControl::execute()
{

}
