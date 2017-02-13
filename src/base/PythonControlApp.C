#include "PythonControlApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"
#include "PythonControl.h"
#include "CoefDiffusionTwo.h"
#include "DirichletBCTwo.h"
#include "TimePostprocessor.h"

template<>
InputParameters validParams<PythonControlApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

PythonControlApp::PythonControlApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PythonControlApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PythonControlApp::associateSyntax(_syntax, _action_factory);
}

PythonControlApp::~PythonControlApp()
{
}

// External entry point for dynamic application loading
extern "C" void PythonControlApp__registerApps() { PythonControlApp::registerApps(); }
void
PythonControlApp::registerApps()
{
  registerApp(PythonControlApp);
}

// External entry point for dynamic object registration
extern "C" void PythonControlApp__registerObjects(Factory & factory) { PythonControlApp::registerObjects(factory); }
void
PythonControlApp::registerObjects(Factory & factory)
{
  registerKernel(CoefDiffusionTwo);

  registerBoundaryCondition(DirichletBCTwo);

  registerPostprocessor(TimePostprocessor);

  registerControl(PythonControl);
}

// External entry point for dynamic syntax association
extern "C" void PythonControlApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { PythonControlApp::associateSyntax(syntax, action_factory); }
void
PythonControlApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
