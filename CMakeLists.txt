cmake_minimum_required(VERSION 3.8)
set(CATCH_TESTS catch_unit_tests)
project(${CATCH_TESTS} C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_DIR include)
set(TEST_DIR tests)

set(Headers 
${INCLUDE_DIR}/catch.hpp
${INCLUDE_DIR}/stl_helper_functions.hpp
)

set(MainCatchTests 
${TEST_DIR}/main_catch_tests.cpp
)

enable_testing()

add_executable(${CATCH_TESTS} ${Headers} ${MainCatchTests})

add_test(
    NAME ${CATCH_TESTS} 
    COMMAND ${CATCH_TESTS}
    )
