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

  //get input file path
  std::string filename = _app.getFileName(false);
  std::string path;
  size_t pos = filename.find_last_of('/');
  if (pos != std::string::npos)
    path = filename.substr(0, pos);
  else
    path = ".";

  //Add to to python path
  std::string python_path = std::string("PYTHONPATH=");
  python_path.append(path);
  if (getenv("PYTHONPATH") != NULL)
  {
    python_path.append(":");
    python_path.append(getenv("PYTHONPATH"));
  }

  char * c_path = new char[python_path.size() + 1];
  python_path.copy(c_path, python_path.size());
  c_path[python_path.size()] = '\0';
  putenv(c_path);
  Moose::out << "Creating PYTHONPATH " << c_path << std::endl;

  //Get python module
  Py_Initialize();
  //The control module name
  std::string control_module = getParam<std::string>("python_file");
  size_t len = control_module.length();
  if (len > 3 && control_module.substr(len - 3, 3) == ".py")
    control_module = control_module.substr(0, len - 3);

  //std::string control_path = path + "/" + control_module + ".py";
  //MooseUtils::checkFileReadable(control_path);

  PyObject *pName;

  pName = PyUnicode_FromString(control_module.c_str());

  pModule = PyImport_Import(pName);

  if (pModule != NULL) {
    fprintf(stderr, "Loaded \"%s\"\n", control_module.c_str());
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", control_module.c_str());
  }
  //Get function in python module
}

void
PythonControl::execute()
{
  //Convert postprocessors to python
  //Convert controlled vars to python
  //call python function
  //Get all controlled vars and put them back in
}
