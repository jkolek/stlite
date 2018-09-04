CXX = g++
CXXFLAGS = -g -std=c++14 -DUSE_STL

INCLUDE_DIR = include
TEST_DIR = test

all:  test1 test2 test_circular_list test_forward_list test_vector test_array \
	  test_set test_stack test_queue

test1: $(INCLUDE_DIR)/circular_list.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test1.cpp -o test1

test2: $(INCLUDE_DIR)/circular_list.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test2.cpp -o test2

test_circular_list: $(INCLUDE_DIR)/circular_list.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_circular_list.cpp -o test_circular_list

test_forward_list: $(INCLUDE_DIR)/forward_list.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_forward_list.cpp -o test_forward_list

test_vector: $(INCLUDE_DIR)/vector.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_vector.cpp -o test_vector

test_array: $(INCLUDE_DIR)/array.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_array.cpp -o test_array

test_set: $(INCLUDE_DIR)/set.h $(INCLUDE_DIR)/algorithms.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_set.cpp -o test_set

test_stack: $(INCLUDE_DIR)/stack.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_stack.cpp -o test_stack

test_queue: $(INCLUDE_DIR)/queue.h
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_queue.cpp -o test_queue

clean:
	-rm test1 test2 test_circular_list test_vector test_array test_set \
	test_stack test_queue test_forward_list
