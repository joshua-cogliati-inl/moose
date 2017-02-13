#ifndef PYTHONCONTROL_H
#define PYTHONCONTROL_H

#include "Control.h"

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
  
};

#endif /* PYTHONCONTROL_H */
