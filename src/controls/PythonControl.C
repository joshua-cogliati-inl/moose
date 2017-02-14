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
  MooseUtils::tokenize(getParam<std::string>("controlled_vars"), _controlled_vars, 1, " ");
  MooseUtils::tokenize(getParam<std::string>("postprocessor_vars"), _postprocessor_vars, 1, " ");

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
  //Moose::out << "Creating PYTHONPATH " << c_path << std::endl;

  //Get python module
  Py_Initialize();
  //The control module name
  std::string control_module = getParam<std::string>("python_file");
  size_t len = control_module.length();
  if (len > 3 && control_module.substr(len - 3, 3) == ".py")
    control_module = control_module.substr(0, len - 3);

  PyObject *python_name;

  python_name = PyUnicode_FromString(control_module.c_str());

  _python_module = PyImport_Import(python_name);
  Py_DECREF(python_name);

  if (_python_module == NULL) {
    PyErr_Print();
    mooseError("Failed to load " << control_module);
  }

  //Get function in python module
  _function = PyObject_GetAttrString(_python_module, "execute");
  if (!_function || !PyCallable_Check(_function)) {
    if (PyErr_Occurred())
      PyErr_Print();
    mooseError("Cannot find function 'execute' in "<< control_module);
  }
}

void
PythonControl::execute()
{
  //Convert postprocessors to python
  PyObject * postprocessor_dict = Py_BuildValue("{}");
  for (const std::string postprocessor : _postprocessor_vars)
  {
    PyObject * value = PyFloat_FromDouble(getPostprocessorValueByName(postprocessor));
    PyDict_SetItemString(postprocessor_dict, postprocessor.c_str(), value);
    Py_DECREF(value);
  }

  //Convert controlled vars to python
  PyObject * controlled_dict = Py_BuildValue("{}");
  for (const std::string controlled : _controlled_vars)
  {
    PyObject * value = PyFloat_FromDouble(getControllableValueByName<Real>(controlled));
    PyDict_SetItemString(controlled_dict, controlled.c_str(), value);
    Py_DECREF(value);
  }

  //call python function
  PyObject * args = PyTuple_New(2);
  PyTuple_SetItem(args, 0, controlled_dict);
  PyTuple_SetItem(args, 1, postprocessor_dict);
  PyObject * ret = PyObject_CallObject(_function, args);
  if (ret == NULL)
    PyErr_Print();

  //Get all controlled vars and put them back in
  for (const std::string controlled : _controlled_vars)
  {
    PyObject * value = PyDict_GetItemString(controlled_dict, controlled.c_str());
    assert(PyNumber_Float(value) != NULL);
    setControllableValueByName<Real>(controlled, PyFloat_AsDouble(value));
  }
  Py_DECREF(args);
  Py_DECREF(postprocessor_dict);
  Py_DECREF(controlled_dict);
}
