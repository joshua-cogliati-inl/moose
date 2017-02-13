#ifndef TIMEPOSTPROCESSOR_H
#define TIMEPOSTPROCESSOR_H

#include "GeneralPostprocessor.h"

class TimePostprocessor;

template<>
InputParameters validParams<TimePostprocessor>();

class TimePostprocessor : public GeneralPostprocessor
{
public:
  TimePostprocessor(const InputParameters & parameters);

  virtual ~TimePostprocessor();
  virtual void initialize();
  virtual void execute();
  virtual Real getValue();

};

#endif
