cmake_minimum_required(VERSION 3.1)

# build library of ADEF

# add source file
set(func_src cm/cf/func/BaseFunction.cpp
             cm/cf/func/DepdFFunction.cpp
             cm/cf/func/IsadeCrFunction.cpp
             cm/cf/func/IsadeFFunction.cpp
             cm/cf/func/JdeCrFunction.cpp
             cm/cf/func/JdeFFunction.cpp
             cm/cf/func/SdeFFunction.cpp
             cm/cf/func/WeightedAverageFunction.cpp
             cm/cf/func/sf/ImprovedPercentageScoringFunction.cpp
             cm/cf/func/sf/SuccessScoringFunction.cpp
)

set(cf_src cm/cf/MultipleControlFunction.cpp
           cm/cf/SingleControlFunction.cpp
)

set(cs_src cm/cs/NonInfoControlSelection.cpp
)

set(cu_src cm/cu/AverageFitnessControlUpdate.cpp
           cm/cu/CurrentFitnessControlUpdate.cpp
           cm/cu/GenerationControlUpdate.cpp
           cm/cu/MaxFitnessControlUpdate.cpp
           cm/cu/MinFitnessControlUpdate.cpp
           cm/cu/SdeFControlUpdate.cpp
)

set(cm_src cm/SadeCrControlMechanism.cpp
           cm/SdeFControlMechanism.cpp
)

set(problem_src problem/basic/QuarticFunctionWithNoise.cpp
)

set(root_src adef.cpp
             BoundedRepair.cpp
             Configuration.cpp
             DEBinomial.cpp
             DECrossover.cpp
             DEEnvironmentalSelection.cpp
             DEMutation.cpp
             DERand.cpp
             DEReproduction.cpp
             DEVariantY.cpp
             Evaluator.cpp
             Evolution.cpp
             Experiment.cpp
             ExperimentalStatistics.cpp
             Individual.cpp
             Initializer.cpp
             JsonConfigurationBuilder.cpp
             Parameters.cpp
             Population.cpp
             Problem.cpp
             PrototypeManager.cpp
             Random.cpp
             ReflectiveRepair.cpp
             Repair.cpp
             Repository.cpp
             Statistics.cpp
             System.cpp
             SystemStatistics.cpp
)

set(adef_source ${func_src}
                ${cf_src}
                ${cs_src}
                ${cu_src}
                ${cm_src}
                ${problem_src}
                ${root_src}
)

# the type of library base on BUILD_SHARED_LIBS
add_library(libadef ${adef_source})

# include dir of libadef
# PRIVATE means only itself include these dir
# INTERFACE means other target used libadef also include these dir
# PUBLIC means both of them
target_include_directories(libadef
                           PUBLIC ${PROJECT_SOURCE_DIR}/${ADEF_INCLUDE_DIR})

# if STATIC, see ARCHIVE_OUTPUT_DIRECTORY
# if SHARED and non-DLL platforms, see LIBRARY_OUTPUT_DIRECTORY
# if SHARED and DLL platforms, see RUNTIME_OUTPUT_DIRECTORY
set_target_properties(libadef PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
                                         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
                                         RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

set_target_properties(libadef PROPERTIES OUTPUT_NAME adef
                                         CXX_STANDARD 14
                                         CXX_STANDARD_REQUIRED ON)

# libadef needs to include json
target_include_directories(libadef
                           PRIVATE ${PROJECT_SOURCE_DIR}/${JSON_INCLUDE_DIR})
