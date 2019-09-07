CC=gcc
CXX=g++
CODE_FORMAT=clang-format
CODE_FORMAT_PARAMS=-i -style=Chromium
RM=rm -f
CPPFLAGS=-Wall -Wextra -Wpedantic -Wno-implicit-conversion -std=c++17 -O3 -Ofast -fexceptions
SRC_DIR=src
TESTS_DIR=tests
BUILD_DIR=build

SRCS=$(TESTS_DIR)\test_main.cpp
HEADERS=$(SRC_DIR)\stl_helper_functions.hpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test

test: $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BUILD_DIR)/test.exe $(OBJS) 


$(TESTS_DIR)\test_main.o: $(TESTS_DIR)/test_main.cpp

format:
	$(CODE_FORMAT) $(CODE_FORMAT_PARAMS) $(HEADERS) $(SRCS)

run:	
	$(BUILD_DIR)/test
	

clean:
	$(RM) $(BUILD_DIR)/test.exe $(TESTS_DIR)/*.o
	