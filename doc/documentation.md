# ADEF Documentation
The documentation is written in many parts and each part follows the section **Diagram**, **Usage**, and **Design issue**. Diagram describes the inheritance relations or workflow. Usage demonstrates how to use operations and its meaning. Design issue explains what problems meet and how to solve.

The usage of configuration format of each classes list on the [API documentation](http://ukjhsa.github.io/adef/).

Table of contents:
- [Prototype](#prototype)
- [PrototypeManager](#prototypemanager)
- [Configuration](#configuration)
- [System, Experiment, and Repository](#system-experiment-and-repository)
- [EvolutionaryState](#evolutionarystate)
- [Evolutionary flow](#evolutionary-flow)
- [ControlMechanism](#controlmechanism)
    - [ControlRange](#controlrange)
    - [ControlParameter](#controlparameter)
    - [ControlSelection](#controlselection)
    - [ControlUpdate](#controlupdate)
    - [ControlFunction](#controlfunction)
- [Function](#function)

## Prototype
http://ukjhsa.github.io/adef/classadef_1_1_prototype.html
##### Diagram
All classes supported the following feature are derived from `Prototype`:
- change the implementation class by class name on the configuration file.
- configure its internal states on the configuration file.

##### Usage
- If a class `A` derived from `Prototype`, it must implements three functions:
    1. `setup(...)` to specify how to configure its internal states.
    2. `clone()` and 
    3. private function `clone_impl()` to support the virtual copy constructor.

```cpp
class A : public Prototype
{
public:
    std::shared_ptr<A> clone() const
    {
        return std::dynamic_pointer_cast<A>(clone_impl());
    }
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        // configure the internal states.
    }
private:
    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<A>(*this);
    }
};
```

- Classes which can change the implementation class by class name must be registered to `PrototypeManager`.

##### Design issue
- To change the implementation class by class name
    - classes must be derived from the base class.
    - ADEF must has the feature such as Reflection. (see `PrototypeManager` below.)
- Why `setup(...)` accept parameter `PrototypeManager`?
    - It is trivial that `Configuration` is used to configure.
    - The class name used to change the implementation class is also a part of the configuration data, therefore it exists to configured.
- The use of virtual copy constructor
    - If we want to copy an individual but we just have its Prototype type, we can call `clone()` to do it.

## PrototypeManager
http://ukjhsa.github.io/adef/classadef_1_1_prototype_manager.html
##### Diagram
`PrototypeManager` contains the map of class name to class instance derived from `Prototype` to support the simple mechanism of [Reflection](https://en.wikipedia.org/wiki/Reflection_(computer_programming)).

##### Usage
- `register_type(...)` to register classes which can change the implementation class by class name in function `adef::register_type(...)` inside `adef::init_adef(...)`.
- `make_type(...)` to return the cloned class for the use.

Some helpful global functions:
- `adef::make_and_setup_type(config, pm)` to get the class name from configuration, then do `make_type(...)` and call `setup(...)` of returning class.
- `adef::make_and_setup_type(name, config, pm)` to get configuration of `name` then do `adef::make_and_setup_type(config, pm)`.

##### Design issue
- The mechanism of Reflection

In order to change the implementation class by class name, there must has a storage that can get the instance by its name.

## Configuration
http://ukjhsa.github.io/adef/classadef_1_1_configuration.html
##### Diagram
![image](adef__ConfigurationDiagram.png)

`Configuration` has member data:
- `ConfigurationData`: store the configuration data.
- `ConfigurationBuilder`: create `ConfigurationData`.

##### Usage
- If configuration file is written in [JSON](http://www.json.org/), then it use `JsonConfigurationBuilder` to create `JsonConfigurationData`.
- There are three kinds of the configuration data:
    - object : consists of members.
        - member: name-value pair. name is `std::string` and value is value accessed by name.
    - array : consists of elements.
        - element: value accessed through the ordered index.
    - value : can be a null, `true`, `false`, `std::string`, number (including `int`, `unsigned int`, and `double`), object or array.
- `load_config(...)` to load the configuration data from the file.
- `is_xxxxx()` to check whether the configuration data belongs to `xxxxx`.
- `get_config(name)` and `get_xxxxx_value(name)` are the use of object.
- `get_config(index)`, `get_array_size()`and `get_xxxxx_value(index)` are the use of array.
- `get_xxxxx_value()` and `get_value<xxxxx>()` are the use of value.

##### Design issue
- Why `ConfigurationData` and `ConfigurationBuilder` exist, are they just JSON?

For the extension of XML or other formats in the future. i.e., `XmlConfigurationData` is designed to derive from `ConfigurationData`.

- The design of interface

They may not complete for other formats.

## System, Experiment, and Repository
System http://ukjhsa.github.io/adef/classadef_1_1_system.html

Experiment http://ukjhsa.github.io/adef/classadef_1_1_experiment.html

Repository http://ukjhsa.github.io/adef/classadef_1_1_repository.html
##### Diagram
![image](adef__SystemLevelDiagram.png)

`System` has member data:
- The name of the current execution.
- `SystemStatistics`: the statistics of total experiments.
- `Experiment`

`Experiment` has member data:
- The name of the experiment.
- The number of runs.
- `ExperimentalStatistics`: the statistics of total runs.
- `Repository`

`Repository` has member data:
- The name of the current algorithm.
- `Evolution`: the evolutionary flow. (see Evolutionary flow below)
- `Problem`: the problem to be solved.
- `Statistics`: the statistics of total generations in a run.
- `Parameters`: the parameters storage.
- `Initializer`: The initializer to initialize population.
- `Evaluator`: The evaluator to evaluate the objectives of individuals.
- `Population`
    - population: the parents of each generation and the population survived to the next generation.
    - offpsring: the offspring of each generation.
- `Reproduction`: The process of reproduction.
- `EnvironmentalSelection`: The process of environmental selection.
- `Mutation`: The process of mutation.
- `Crossover`: The process of crossover.
- `Repair`: The process of repairing invalid individuals.

`System` has many `Experiment`, each `Experiment` has one `Repository`, and `Repository` has total evolutionary states. (see EvolutionaryState below)

##### Usage
- Users call `System::run()` to execute and it uses `Experiment::run()` inside to start evolution according to `Evolution::evolve(...)`.
- Output statistics at the end of run
    - best, worst, mean, standard deviation, and success performance. See `SystemStatistics`.
    - FEs, error, and best fitness on each experiment. See `ExperimentalStatistics`.

##### Design issue
- What is the difference between `System` and `Experiment`?

The system can have one or many experiments and output statistics of all experiments.

- What is the difference between `Experiment` and `Repository`?

`Experiment` has informations that includes the number of runs and what algorithm, stored in `Repository`, to be used.

- Why there need `Repository` to contain informations of the algorithm?

Because the parameters of function is variable in different evolutionary process, ADEF encapsulates them into the single parameter `Repository` so that we can extract interface to use. Therefore operations of `Repository` are just getters.

## EvolutionaryState
http://ukjhsa.github.io/adef/classadef_1_1_evolutionary_state.html
##### Diagram
The following classes participate the evolutionaray process:
- Evolution
- Initializer
- Evaluator
- Reproduction
- Mutation
- Crossover
- EnvironmentalSelection
- Repair
- Population
- Individual
- Problem
- Statistics
- Parameters

##### Usage
- If a class `A` derived from `EvolutionaryState`, it must implements function:
    - `init(...)` to initialize the current state from other states if needed.

```cpp
class A : public EvolutionaryState
{
public:
    void init(std::shared_ptr<Repository> repos) override
    {
        // initialize the internal states from other states if needed.
    }
};
```

##### Design issue
- What initialization needs informations from others?

For example, the initialization of the dimension of decision variables of `Individual` needs the dimension of decision space from `Problem`.

## Evolutionary flow
##### Diagram
![image](evolution__flow.png)

The basic flow of Evolutionary algorithm inside `Evolution::evolve(...)`.

##### Usage
- Users only need to implement `Reproduction` or `EnvironmentalSelection` or their derived classes if the flow satisfied.
- The order of `Mutation`, `Crossover` and `Repair` in `Reproduction` are flexible
    - in DE, their order is `Mutation`, `Crossover` then `Repair`. See `DEReproduction`.
    - in GA, their order maybe is `Crossover`, `Mutation` then `Repair`.
- `Statistics` is used after the following position:
    - `Initializer`: statistics of the initial population.
    - `Reproduction`: statistics of the population of parents and offsprings on each generation.
    - `EnvironmentalSelection`: statistics of the current population on each generation.

##### Design issue
- Why the choice of implementing different `Reproduction` and `EnvironmentalSelection` instead of implementing different `Evolution` on the Evolutionary flow?

Implementing different `Evolution` is an alternative, but here ADEF want users written each operators likes mutation or crossover to focus on the feature of changing implementation classes dynamically. Overriding the flow only when it is necessary. And `Reproduction` too.

## ControlMechanism
http://ukjhsa.github.io/adef/classadef_1_1_base_control_mechanism.html
##### Diagram
![image](adef__ControlMechanismDiagram.png)

`ControlMechanism` has member data
- `ControlRange`: the range of the object.
- `ControlParameter`: the object storage.
- `ControlSelection`: the operation of how to update by the relation between parent and offspring.
- `ControlUpdate`: the operation of how to update by the current state.
- `ControlFunction`: the function storage.

`ControlMechanism` is derived from `BaseControlMechanism`, the base abstract class, and has Subclasses:
- `SadeCrControlMechanism`: used by parameter CR in the SaDE algorithm.
- `SdeFControlMechanism`: used by parameter F in the SDE algorithm.
- `IndirectControlMechanism`: used by parameter F in the both NSDE and SaNSDE algorithm.

##### Usage
If there is a parameter which is declared by `ControlMechanism`, the suggested usage are:

1. call `update(...)` firstly.
2. call `generate(...)` when you want to get the new parameter.

And call `select(...)` after `Reproduction` or inside `EnvironmentalSelection`. (see Design issue of this section)

The parameter *F* and *CR* in DE:
The parameter *F* is the member data of `DEMutation` and *CR* is the member data of `DECrossover`. Both parameters are declared by `BaseControlMechanism`. They should be stored to `Parameters` to let `DEEnvironmentalSelection` have the ability to use them.

##### Design issue
- Why parameters *F* and *CR* are declared by `BaseControlMechanism`?
    - They are not necessary to expose the template type of `ControlMechanism` to other evolutionary states, so `DEEnvironmentalSelection` does.
    - `dynamic_cast` to actual type only on the use of `generate(...)`,i.e., in `DEMutation` and `DECrossover`.
- Why the use of calling `select(...)` inside `EnvironmentalSelection`?

`select(...)` uses the relation between parent and offspring so it must be called after `Reproduction` which reproduces complete offspring.

- Why parameters *F* and *CR* are the member data of `DEMutation` and `DECrossover`?
    - This issue has no absolute solution. ADEF takes the reason they just come from mutation and crossover.

### ControlRange
http://ukjhsa.github.io/adef/classadef_1_1_control_range.html
##### Diagram
`ControlRange` has template specialization for the Object type
- arithmetic type
    - has member data the lower bound and upper bound of the valid object
- non-arithmetic type
    - has nothing

##### Usage
- `is_valid(...)` to check whether the object is in the range. If the Object type is not arithmetic, it do nothing.

##### Design issue
- The template specialization for non-arithmetic type

In current version, the type is `std::shared_ptr<RealFunction>` and it has no concept of valid range.

### ControlParameter
http://ukjhsa.github.io/adef/classadef_1_1_control_parameter.html
##### Diagram
![image](adef__ControlParameterSubsystem__ControlParameterDiagram.png)

It is the object storage.

`SingleControlParameter` manages only one object while `MultipleControlParameter` manages many objects.

##### Usage
- `save(object, index)` to store the object.
- `load(index)` to load the object.
- `number_of_objects()` to return the number of objects.

The following operations manages the flag of already generated:
- `is_already_generated(index)` to return the flag.
- `reset_already_generated(index)` to reset the flag.

Their usage are

```
if (is_already_generated(index))
{
    return old object loaded from ControlParameter
}
else {
    generate new object
    save new object to ControlParameter
    return new object
}
```

##### Design issue
- What the use does `BaseControlParameter` have?

It is not necessary to expose the template type of `ControlParameter` to all `ControlSelection` and `ControlUpdate`. For examples, `MaxFitnessControlUpdate` does not load object from it, but `SdeFControlUpdate` does.

- Why `is_already_generated(index)` and `reset_already_generated(index)` exist?
    - avoid repeating the same calculation for the efficiency.
    - let `Function` returns the same result for those are stochastic on each call likes `RandomSelectionFunction`.

- What the difference between `SingleControlParameter` and `MultipleControlParameter`?
    - one object vs. many objects.
    - the former ignores the parameter `index` of functions.

### ControlSelection
http://ukjhsa.github.io/adef/classadef_1_1_control_selection.html
##### Diagram
![image](adef__ControlSelectionSubsystem__ControlSelectionDiagram.png)

##### Usage

##### Design issue

### ControlUpdate
http://ukjhsa.github.io/adef/classadef_1_1_control_update.html
##### Diagram
![image](adef__ControlUpdateSubsystem__ControlUpdateDiagram.png)

##### Usage

##### Design issue

### ControlFunction
http://ukjhsa.github.io/adef/classadef_1_1_control_function.html
##### Diagram
![image](adef__ControlFunctionSubsystem__ControlFunctionDiagram.png)

##### Usage

##### Design issue

## Function
##### Diagram

##### Usage

##### Design issue
