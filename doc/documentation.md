# ADEF Documentation
The documentation is written in many parts and each part follows the section **Diagram**, **Usage**, and **Design issue**. Diagram describes the inheritance relations or workflow. Usage demonstrates how to use operations and its meaning. Design issue explains what problems meet and how to solve.

The usage of configuration format of each classes list on the [API documentation](http://ukjhsa.github.io/adef/).

## Prototype
##### Diagram
All classes derived from Prototype support the following feature
- change the implementation class by class name on the configuration file.
- configure its internal states on the configuration file.

see http://ukjhsa.github.io/adef/db/d2e/classadef_1_1_prototype.html

##### Usage
- If the class `A` derived from Prototype, it must implements functions:
    - `setup(const Configuration &, const PrototypeManager &)` to specify how to configure its internal states.
    - public `std::shared_ptr<A> clone() const` and private `std::shared_ptr<Prototype> clone_impl() const` to support the virtual copy constructor by calling `clone()`.
- Classes derived from Prototype are registered to PrototypeManager when calling adef::init_adef(). (see PrototypeManager below.)

##### Design issue
- To change the implementation class by class name
    - classes must inherit the base class. (for changing.)
    - ADEF must has the support of Reflection. (for changing by class name.) (see PrototypeManager below.)
- Why `setup(const Configuration &, const PrototypeManager &)` accept parameter PrototypeManager?
    - Configuration used to configure by the configuration data is trivial.
    - The class name used to change the implementation class is considered a part of the configuration data, so it can configure it.
- The use of virtual copy constructor
    - If we want to copy an individual but we just have its Prototype type, we can call `clone()` to do it.

## PrototypeManager and Configuration
##### Diagram
PrototypeManager implements the simple mechanism of C++ reflection. see http://ukjhsa.github.io/adef/de/d50/classadef_1_1_prototype_manager.html

Configuration provides interfaces to access configuration data and has two member data:
- ConfigurationData
- ConfigurationBuilder

see http://ukjhsa.github.io/adef/d6/d8f/classadef_1_1_configuration.html

##### Usage

##### Design issue

## System, Experiment, and Repository
##### Diagram

##### Usage

##### Design issue

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
