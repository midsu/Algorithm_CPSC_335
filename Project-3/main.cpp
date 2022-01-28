#include <iomanip>
#include <iostream>
#include <cassert>

#include "rubrictest.hpp"
#include "SensorCluster.hpp"

int main() {
	
  Rubric rubric;
  
  // test hash functions
  rubric.criterion("hash function 1 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct1(123456)", 1, hashfct1(123456U) );
		   });
  
  rubric.criterion("hash function 2 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct2(123456)", 2, hashfct2(123456U) );
		   });
  
  rubric.criterion("hash function 3 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct3(123456)", 3, hashfct3(123456U) );
		   });
  
  rubric.criterion("hash function 4 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct4(123456)", 4, hashfct4(123456U) );
		   });
  
  rubric.criterion("hash function 5 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct5(123456)", 5, hashfct5(123456U) );
		   });
  
  rubric.criterion("hash function 6 item 123456", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct6(123456)", 6, hashfct6(123456U) );
		   });
  
  rubric.criterion("hash function 1 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct1(678901)", 6, hashfct1(678901U) );
		   });
  
  rubric.criterion("hash function 2 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct2(678901)", 7, hashfct2(678901U) );
		   });
  
  rubric.criterion("hash function 3 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct3(678901)", 8, hashfct3(678901U) );
		   });
  
  rubric.criterion("hash function 4 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct4(678901)", 9, hashfct4(678901U) );
		   });
  
  rubric.criterion("hash function 5 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct5(678901)", 0, hashfct5(678901U) );
		   });
  
  rubric.criterion("hash function 6 item 678901", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct6(678901)", 1, hashfct6(678901U) );
		   });
  
  SensorNIC network1;
  network1.addItem("Velocity sensor", 123456U);
  network1.addItem("Particle sensor", 234567U);
  rubric.criterion("size after adding two NICs", 1,
		   [&]() {
      TEST_EQUAL( "size after adding two NICs", 2, network1.size() );
		   });

  SensorNIC network2;
  network2.readTextfile("in1.txt");
  rubric.criterion("size after reading in1.txt", 1,
		   [&]() {
      TEST_EQUAL( "size after reading in1.txt", 18, network2.size() );
           });
  
  rubric.criterion("bestHashing() for in1.txt", 1,
		   [&]() {
     TEST_EQUAL( "bestHashing() for in1.txt", 2, network2.bestHashing() );
		   });
  
  SensorNIC network3;
  network3.readTextfile("in2.txt");
  rubric.criterion("size after reading in2.txt", 1,
		   [&]() {
      	     TEST_EQUAL( "size after reading in2.txt", 37, network3.size());
		   });
  
  rubric.criterion("bestHashing() for in2.txt", 1,
                   [&]() {
      	     TEST_EQUAL( "bestHashing() for in2.txt", 3, network3.bestHashing());
                   });
  
  /*
    SensorNIC changed_network3(network3);
  changed_network3.removeItem(889012);
  */
  SensorNIC changed_network3;
  changed_network3.readTextfile("in2.txt");
  changed_network3.removeItem(889012);
    
  rubric.criterion("size after removing 889012", 1,
		   [&]() {
      TEST_EQUAL( "size after removing 889012", 36, changed_network3.size() );
		   });
  
  rubric.criterion("hash function 1", 1,
		   [&]() {
TEST_EQUAL( "bestHashing() after removing 889012", 6, changed_network3.bestHashing() );
		   });
    
  return rubric.run();
}
