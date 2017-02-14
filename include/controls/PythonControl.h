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
  std::vector<std::string> _controlled_vars;
  std::vector<std::string> _postprocessor_vars;
  PyObject * _python_module, * _function;
};

#endif /* PYTHONCONTROL_H */
