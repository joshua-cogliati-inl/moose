#ifndef PYTHONCONTROL_H
#define PYTHONCONTROL_H

#include "Control.h"
#include <Python.h>

class PythonControl;

template<>
InputParameters validParams<PythonControl>();

class PythonControl : public Control
{
public:

  PythonControl(const InputParameters & parameters);

  virtual void execute() override;

private:
  std::vector<std::string> controlled_vars;
  std::vector<std::string> postprocessor_vars;
  PyObject * pModule, * pFunction;
};

#endif /* PYTHONCONTROL_H */
