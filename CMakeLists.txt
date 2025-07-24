cmake_minimum_required(VERSION 3.16)
project(stl_helper_functions_library VERSION 0.2.0)
project(stl_helper_functions_library CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CATCH_TESTS catch_unit_tests)

if (MSVC)
    # add_compile_options(/nologo /W4 /EHsc /std:latest /Ot /Ox /Ob2 /Oy /Oi /GL)
    # add_compile_options(/nologo /Wall /sdl /EHsc /std:latest /Od /GS /GR)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /nologo /W4 /EHsc /std:latest /Ot /Ox /Ob2 /Oy /Oi /GL")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /nologo /Wall /sdl /EHsc /std:latest /Od /GS /GR")
else ()
    # add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-variable -Wno-format-security -std=c++20 -O3 -Ofast)
    # add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-variable -Wno-format-security -Wconversion -std=c++20 -g -O0)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -Wpedantic -O3 -Ofast -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic -g -O0 -DGLIBCXX_DEBUG")
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
