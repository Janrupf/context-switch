###################
# Test Subproject #
###################

###################
# Add manual test #
###################
set(CONTEXT_SWITCH_MANUAL_TEST_SRC
        ${CMAKE_CURRENT_LIST_DIR}/manual/main.cpp)

add_executable(context-switch-manual-test ${CONTEXT_SWITCH_MANUAL_TEST_SRC})
target_link_libraries(context-switch-manual-test PUBLIC context-switch)

##############################
# Search and check for GTest #
##############################
find_package(GTest)
if(NOT GTest_FOUND)
    message(STATUS "GTest not found, disabling unit tests")
    return()
endif()

########################
# Add unit test target #
########################
set(CONTEXT_SWITCH_UNIT_TEST_SRC
        ${CMAKE_CURRENT_LIST_DIR}/unit/basic.cpp)
add_executable(context-switch-unit-test ${CONTEXT_SWITCH_UNIT_TEST_SRC})
target_link_libraries(context-switch-unit-test PUBLIC context-switch GTest::Main)