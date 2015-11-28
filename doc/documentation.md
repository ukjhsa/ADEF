# ADEF Documentation
The documentation is written in many parts and each part follows the section **Diagram**, **Usage**, and **Design issue**. Diagram describes the inheritance relations or workflow. Usage demonstrates how to use operations and its meaning. Design issue explains what problems meet and how to solve.

The usage of configuration format of each classes list on the [API documentation](http://ukjhsa.github.io/adef/).

## Prototype
##### Diagram
All classes supported the following feature are derived from it:
- change the implementation class by class name on the configuration file.
- configure its internal states on the configuration file.

see http://ukjhsa.github.io/adef/db/d2e/classadef_1_1_prototype.html

##### Usage
- If a class derived from `Prototype`, it must implements three functions:
    - `setup(...)` to specify how to configure its internal states.
    - public `clone()` and private `clone_impl()` to support the virtual copy constructor.
- Classes which can change the implementation class by class name are registered to `PrototypeManager`.

##### Design issue
- To change the implementation class by class name
    - classes must inherit the base class.
    - ADEF must has the feature such as Reflection. (see `PrototypeManager` below.)
- Why `setup(...)` accept parameter `PrototypeManager`?
    - Configuration used to configure by the configuration data is trivial.
    - The class name used to change the implementation class is also a part of the configuration data, therefore it can be configured.
- The use of virtual copy constructor
    - If we want to copy an individual but we just have its Prototype type, we can call `clone()` to do it.

## PrototypeManager
##### Diagram
It implements the simple mechanism of [Reflection](https://en.wikipedia.org/wiki/Reflection_(computer_programming)). It contains the map of class name to class instance.

see http://ukjhsa.github.io/adef/de/d50/classadef_1_1_prototype_manager.html

##### Usage
- `register_type(...)` to register classes which can change the implementation class by class name in function `adef::register_type(...)` in `adef::init_adef(...)`.
- `make_type(...)` to return the cloned class for the use.
- `adef::make_and_setup_type(config, pm)` to get the class name from configuration, then do `make_type(...)` and call `setup(...)` of returning class.
- `adef::make_and_setup_type(name, config, pm)` to get configuration of name and do `adef::make_and_setup_type(config, pm)`.

##### Design issue
- the mechanism of Reflection
    - because we want to change the implementation class by class name, there must has a storage that can get the instance by its name.
    - `PrototypeManager` is the storage and each class registered is derived from `Prototype`.

## Configuration
##### Diagram
![image]()

It provides interfaces to access configuration data and has two member data:
- `ConfigurationData`: store the configuration data.
- `ConfigurationBuilder`: create `ConfigurationData`.

If configuration file is written in [JSON](http://www.json.org/), then it use `JsonConfigurationBuilder` to create `JsonConfigurationData`.

see http://ukjhsa.github.io/adef/d6/d8f/classadef_1_1_configuration.html

##### Usage
There are three kinds of the configuration data:
- object : consists of members.
    - member: name-value pair. name is string and value is value accessed by name.
- array : consists of elements.
    - element: value accessed through the ordered index.
- value : can be a null, true, false, string, number (including int, unsigned int, and double), object or array.

- `load_config(...)` to Load the configuration data from the file.
- `is_xxxxx()` to check whether the configuration data belongs to `xxxxx`.
- `get_config(name)` and `get_xxxxx_value(name)` are the use of object.
- `get_config(index)`, `get_array_size()`and `get_xxxxx_value(index)` are the use of array.
- `get_xxxxx_value()` and `get_value<xxxxx>()` are the use of value.

##### Design issue
- Why `ConfigurationData` and `ConfigurationBuilder` exist, are they just JSON?
For the extension of XML or other format in the future. i.e., `XmlConfigurationData` is derived from `ConfigurationData`.
- The design of interface
There may not complete in the current version.

## System, Experiment, and Repository
##### Diagram
![image]()

`System` has many `Experiment`, and each `Experiment` has one `Repository`.

The difference between `Experiment` and `Repository`:
- `Experiment` has informations of the experiment including the number of runs and what algorithm used.
- `Repository` contains the evolutionary state used in algorithm (see `EvolutionaryState` below.)

see http://ukjhsa.github.io/adef/df/da7/classadef_1_1_system.html, http://ukjhsa.github.io/adef/dd/d93/classadef_1_1_experiment.html, http://ukjhsa.github.io/adef/dd/d2d/classadef_1_1_repository.html

##### Usage
- `System::run()` to execute experiments and inside call `Experiment::run()` to execute the algorithm through `Evolution::run()`.
- Output statistics at the end of run
    - best, worst, mean, standard deviation, and success performance. See `SystemStatistics`.
    - FEs, error, and best fitness for each `Experiment`. See `ExperimentStatistics`.

##### Design issue
- Why split it to `System` and `Experiment`?
The system can have one or many experiments and output statistics of all experiments.
- Why split it to `Experiment` and `Repository`?
The experiment can have the same or different number of runs and algorithm.
- Why `Repository` exists?
In different evolutionaray process, parameters they need is variable, so ADEF encapsulates them into the single parameter, that is `Repository`. Therefore, operations of `Repository` are just many getters.

## EvolutionaryState
##### Diagram

##### Usage

##### Design issue

## Evolutionary flow
##### Diagram

##### Usage

##### Design issue

## ControlMechanism
##### Diagram

##### Usage

##### Design issue

### ControlRange
##### Diagram

##### Usage

##### Design issue

### ControlParameter
##### Diagram

##### Usage

##### Design issue

### ControlFunction
##### Diagram

##### Usage

##### Design issue

### ControlSelection
##### Diagram

##### Usage

##### Design issue

### ControlUpdate
##### Diagram

##### Usage

##### Design issue

## Function
##### Diagram

##### Usage

##### Design issue
