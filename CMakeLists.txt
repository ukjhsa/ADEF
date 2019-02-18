cmake_minimum_required(VERSION 3.1)

project(adef CXX)

option(GENERATE_EXECUTABLE "Generate the executable file" ON)
option(BUILD_SHARED_LIBS "Build adef as the shared library" OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()


set(ADEF_INCLUDE_DIR include)
set(JSON_INCLUDE_DIR thirdparty/json)


# build libadef
add_subdirectory(src)

# generate executable file
if(GENERATE_EXECUTABLE)
    set(main_source src/main.cpp)
    add_executable(adef ${main_source})

    # link to libadef
    target_link_libraries(adef PRIVATE libadef)

    set_target_properties(adef PROPERTIES
                          OUTPUT_NAME adef
                          RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
                          CXX_STANDARD 17
                          CXX_STANDARD_REQUIRED ON)

    # copy the default configuration file
    #file(COPY ${PROJECT_SOURCE_DIR}/config.json DESTINATION ${PROJECT_BINARY_DIR}/)
    add_custom_command(TARGET adef POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config.json ${PROJECT_BINARY_DIR}/config.json)
endif()
