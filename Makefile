CC=gcc
CXX=g++
CODE_FORMAT=clang-format
CODE_FORMAT_PARAMS=-i -style=Chromium
RM=rm -f
CPPFLAGS=-Wall -Wextra -Wpedantic -std=c++17 -O3 -Ofast
SRC_DIR=src
TESTS_DIR=tests
BUILD_DIR=build

SRCS=$(SRC_DIR)\stl_helper_functions.cpp $(TESTS_DIR)\test_main.cpp
HEADERS=$(SRC_DIR)\stl_helper_functions.hpp
OBJS=$(subst .cc,.o,$(SRCS))

all: test

test: $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BUILD_DIR)/test.exe $(OBJS) 


$(SRC_DIR)\stl_helper_functions.o: $(SRC_DIR)/stl_helper_functions.cpp $(SRC_DIR)/stl_helper_functions.hpp

$(TESTS_DIR)\test_main.o: $(TESTS_DIR)/test_main.cpp

format:
	$(CODE_FORMAT) $(CODE_FORMAT_PARAMS) $(HEADERS) $(SRCS)

run:	
	$(BUILD_DIR)/test
	

clean:
	$(RM) $(BUILD_DIR)/test.exe $(BUILD_DIR)/*.o $(BUILD_DIR)/*.obj
	