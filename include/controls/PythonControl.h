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

  static bool keepGoing();
  static void stopGoing();

private:
  std::vector<std::string> _controlled_vars;
  std::vector<std::string> _postprocessor_vars;
  PyObject * _python_module, * _function, * _keep_going_function;
  static bool _keep_going;
};

#endif /* PYTHONCONTROL_H */
