cmake_minimum_required(VERSION 3.1)

# build library of ADEF

# add source file
set(adef_source adef.cpp
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
                ReflectiveRepair.cpp
                Repair.cpp
                Repository.cpp
                Statistics.cpp
                System.cpp
                SystemStatistics.cpp
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
