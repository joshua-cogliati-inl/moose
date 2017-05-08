#ifndef TRIGGERTRANSIENT_H
#define TRIGGERTRANSIENT_H

#include "Transient.h"

class TriggerTransient;

template<>
InputParameters validParams<TriggerTransient>();

class TriggerTransient : public Transient
{
public:
  TriggerTransient(const InputParameters & params);
  virtual ~TriggerTransient();

  virtual bool keepGoing() override;
};

#endif /* TRIGGERTRANSIENT_H */
