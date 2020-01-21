CC=gcc
CXX=g++
CODE_FORMAT=clang-format
CODE_FORMAT_PARAMS=-i -style=Chromium
RM=rm -f
CPPFLAGS=-Wall -Wextra -Wpedantic -std=c++17 -fpermissive -O3
INCLUDE_DIR=include
SRC_DIR=src
TESTS_DIR=tests
BUILD_DIR=build

SRCS=$(TESTS_DIR)/main_catch_tests.cpp
HEADERS=$(INCLUDE_DIR)/stl_helper_functions.hpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test	

test: $(OBJS)
	mkdir -p $(BUILD_DIR) && $(CXX) $(CPPFLAGS) $(OBJS) -o $(BUILD_DIR)/test


$(TESTS_DIR)/main_catch_tests.o: $(TESTS_DIR)/main_catch_tests.cpp

format:
	$(CODE_FORMAT) $(CODE_FORMAT_PARAMS) $(HEADERS) $(SRCS) $(TESTS_DIR)/main_google_tests.cpp

run:	
	chmod +x $(BUILD_DIR)/test && $(BUILD_DIR)/test	

clean:
	$(RM) $(TESTS_DIR)/*.o $(BUILD_DIR)/test