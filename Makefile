CXX = g++
CXXFLAGS = -g -std=c++11

all:  test1 test2 test_list test_vector

test1: linkedlist.h
	$(CXX) $(CXXFLAGS) test1.cpp -o test1

test2: linkedlist.h
	$(CXX) $(CXXFLAGS) test2.cpp -o test2

test_list: linkedlist.h
	$(CXX) $(CXXFLAGS) test_list.cpp -o test_list

test_vector: vector.h
	$(CXX) $(CXXFLAGS) test_vector.cpp -o test_vector

clean:
	-rm test1 test2 test_list test_vector
