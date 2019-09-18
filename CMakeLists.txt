cmake_minimum_required(VERSION 3.8)
set(This STL_helper_functions_library)
project(${This} C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_DIR include)
set(TEST_DIR tests)

set(Headers 
${INCLUDE_DIR}/stl_helper_functions.hpp
)

set(Sources 
${TEST_DIR}/main_google_tests.cpp
)

enable_testing()
add_subdirectory(googletest)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC gtest_main gtest)

add_test(
    NAME ${This} 
    COMMAND ${This}
    )
