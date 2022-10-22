CC=gcc
CXX=g++
CODE_FORMAT=clang-format
CODE_FORMAT_PARAMS=-i -style=Chromium
RM=rm
CPPFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-format-security -O3 -Ofast
INCLUDE_DIR=include
SRC_DIR=src
TESTS_DIR=tests
BUILD_DIR=build

SRCS=$(TESTS_DIR)/main_catch_tests.cpp
HEADERS=$(INCLUDE_DIR)/stl_helper_functions.hpp $(INCLUDE_DIR)/detail/stl_helper_functions_impl.hpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

test: $(OBJS)
	mkdir -p $(BUILD_DIR) && $(CXX) $(CPPFLAGS) $(OBJS) -o $(BUILD_DIR)/test


$(TESTS_DIR)/main_catch_tests.o: $(TESTS_DIR)/main_catch_tests.cpp

format:
	$(CODE_FORMAT) $(CODE_FORMAT_PARAMS) $(HEADERS) $(SRCS)

run:
	chmod +x $(BUILD_DIR)/test && $(BUILD_DIR)/test

clean:
	$(RM) -rf $(BUILD_DIR)
