CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

all: mat_op

mat_op: mat_op.cpp
	$(CXX) $(CXXFLAGS) -o mat_op mat_op.cpp

clean:
	rm -f mat_op
