
CXX = g++ -std=c++17 -Wall

all: run_test cranes_timing

run_test: cranes_test
	./cranes_test

headers: rubrictest.hpp cranes_types.hpp cranes_algs.hpp

cranes_test: headers cranes_test.cpp
	${CXX} cranes_test.cpp -o cranes_test

cranes_timing: headers cranes_timing.cpp
	${CXX} cranes_timing.cpp -o cranes_timing

clean:
	rm -f cranes_test cranes_timing
