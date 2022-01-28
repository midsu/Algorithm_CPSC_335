
GXX49_VERSION := $(shell g++-4.9 --version 2>/dev/null)

ifdef GXX49_VERSION
	CXX_COMMAND := g++-4.9
else
	CXX_COMMAND := g++
endif

CXX = ${CXX_COMMAND} -std=c++17 -Wall

run_test: maxweight_test
	./maxweight_test

headers: rubrictest.hh maxweight.hh

maxweight_test: headers maxweight_test.cc
	${CXX} maxweight_test.cc -o maxweight_test

clean:
	rm -f maxtime_test
