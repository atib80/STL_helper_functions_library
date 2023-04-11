cmake_minimum_required(VERSION 3.8)
project(stl_helper_functions_library VERSION 0.2.0)
project(stl_helper_functions_library CXX)

set(CMAKE_CXX_STANDARD 17)
set(CATCH_TESTS catch_unit_tests)

if (MSVC)
    add_compile_options(/nologo /W4 /EHsc)
    #add_compile_options(/nologo /Wall /sdl /EHsc /Od /GS /GR)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-format-security)
endif ()

set(INCLUDE_DIR include)
set(TEST_DIR tests)

set(Headers
        ${INCLUDE_DIR}/catch.hpp
        ${INCLUDE_DIR}/stl_helper_functions.hpp
        ${INCLUDE_DIR}/detail/stl_helper_functions_impl.hpp
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
