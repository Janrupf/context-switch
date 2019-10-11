cmake_minimum_required(VERSION 3.15)
project(context_switch CXX ASM)

#####################
# Configure options #
#####################
set(CMAKE_CXX_STANDARD 17)
option(CONTEXT_SWITCH_BUILD_TESTS "Wether to build the library tests" OFF)

########################
# Collect source files #
########################
set(CONTEXT_SWITCH_SOURCE
        ${CMAKE_CURRENT_LIST_DIR}/src/context_switch.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/context_switch.S
        ${CMAKE_CURRENT_LIST_DIR}/src/stack.cpp)

set(CONTEXT_SWITCH_INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/include)

#############################
# Add context-switch target #
#############################
if(BUILD_SHARED_LIBS)
    add_library(context-switch SHARED ${CONTEXT_SWITCH_SOURCE})
else()
    add_library(context-switch STATIC ${CONTEXT_SWITCH_SOURCE})
endif()
target_include_directories(context-switch PUBLIC ${CONTEXT_SWITCH_INCLUDE_DIR})

###############
# Subprojects #
###############
if(CONTEXT_SWITCH_BUILD_TESTS)
    add_subdirectory(test)
endif()