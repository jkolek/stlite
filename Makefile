CXX = g++
CXXFLAGS = -g -std=c++11

all:  test1 test2 test_list test_vector test_set test_stack test_queue

test1: list.h
	$(CXX) $(CXXFLAGS) test1.cpp -o test1

test2: list.h
	$(CXX) $(CXXFLAGS) test2.cpp -o test2

test_list: list.h
	$(CXX) $(CXXFLAGS) test_list.cpp -o test_list

test_vector: vector.h
	$(CXX) $(CXXFLAGS) test_vector.cpp -o test_vector

test_set: set.h algorithms.h
	$(CXX) $(CXXFLAGS) test_set.cpp -o test_set

test_stack: stack.h
	$(CXX) $(CXXFLAGS) test_stack.cpp -o test_stack

test_queue: queue.h
	$(CXX) $(CXXFLAGS) test_queue.cpp -o test_queue

clean:
	-rm test1 test2 test_list test_vector test_set test_stack test_queue
