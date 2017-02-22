CXX = g++
CXXFLAGS = -g -std=c++11

all:  test1 test2

test1: linkedlist.h
	$(CXX) $(CXXFLAGS) $(THREAD) test1.cpp -o test1

test2: linkedlist.h
	$(CXX) $(CXXFLAGS) $(THREAD) test2.cpp -o test2

clean:
	-rm test1 test2
