#ifndef TRIGGERTRANSIENT_H
#define TRIGGERTRANSIENT_H

#include "Transient.h"

class TriggerTransient;

template<>
InputParameters validParams<TriggerTransient>();

/**
 * This executioner is a Transient executioner that can also be stopped
 * by a PythonControl's python keep_going function.
 */
class TriggerTransient : public Transient
{
public:
  /**
   * Constructor
   *
   * @param parameters The parameters object holding data for the class to use.
   */
  TriggerTransient(const InputParameters & params);

  /**
   * This returns if the simulation should keep going. It will stop for
   * all the reasons Transient will stop, as well as if PythonControl
   * wants to stop.
   * @return true if this simulation should keep going.
   */
  virtual bool keepGoing() override;
};

#endif /* TRIGGERTRANSIENT_H */
