
CXX = g++ -std=c++17 -Wall

all: run_test

run_test: sensor_test
	./sensor_test

headers: rubrictest.hpp SensorCluster.hpp

sensor_test: headers SensorCluster.cpp main.cpp
	${CXX} SensorCluster.cpp main.cpp -o sensor_test

clean:
	rm -f sensor_test
