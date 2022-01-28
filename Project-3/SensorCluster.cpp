#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int nic) {
  // TODO: implement this function, then delete the return statement below
  unsigned int mod = nic / 100000;
  mod = mod % 10;
  
  //char *str = itoa(nic);//turn into a string 
 // string s = string(str);
 // char first = str.front();//.at(1) for the next
  
  return mod;//first
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
   unsigned int mod = nic / 10000;
   mod = mod % 10;
	return mod;
    
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
   unsigned int mod = nic / 1000;
   mod = mod % 10;
	 return mod;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
   unsigned int mod = nic / 100;
   mod = mod % 10;
	return mod;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
    unsigned int mod = nic / 10;
   mod = mod % 10;
	return mod;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
    unsigned int mod = nic / 1;
   mod = mod % 10;
	return mod;
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void SensorNIC::addItem(string itemName, unsigned int nic) {
  // TO BE COMPLETED(attempted)
  // function that adds the specified NIC to the sensor network (i.e., to all hash tables)
  Item newItem(itemName, nic);

  hT1[nic] = newItem;
  hT2[nic] = newItem;
  hT3[nic] = newItem;
  hT4[nic] = newItem;
  hT5[nic] = newItem;
  hT6[nic] = newItem;

}

bool SensorNIC::removeItem(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below

  // function that removes the sensor specified by the nic value from the network
  // if sensor is found, then it is removed and the function returns true
  // else returns false
    if(hT1.erase(nic) && hT2.erase(nic) && hT3.erase(nic) && hT4.erase(nic) && hT5.erase(nic) && hT6.erase(nic))//if found and erased
    {
      return true;
    }
      
  return false;
}

unsigned int get_balance(std::unordered_map<unsigned int, Item, decltype(&hashfct1)> hash){
  unsigned int maximim = 0;
  unsigned int minimum = 9999;
  unsigned int balance = 0;
  for(unsigned i = 0; i < 10; ++i)
    {
      int size = hash.bucket_size(i);
      if(size > maximim)
      {
        maximim = size;
      }
      if(size < minimum)
      {
        minimum = size;
      }

    }
    balance = maximim - minimum;
    return balance;
}
unsigned int SensorNIC::bestHashing() {
  // TODO: implement this function, then delete the return statement below
    
  // function that decides the best hash function, i.e. the ones among
  // fct1-fct6 that creates the most balanced sensor network for the current
  // set of NIC addresses, i.e. data member allItems

	// Hints:
	// Calculate the balance of each hashtable, one by one.
	/*
	 for (unsigned i=0; i<10; ++i) {
    cout << hT1.bucket_size(i); // Call bucket_size() to get the size of each bucket
  }
	*/
	// Then, calculate the lowest balance
  //int maximim = 0;
  //int minimum = 9999;
  unsigned int balance = 0;
  unsigned int table;
  unsigned int best_balance = 0;

//for ht1
    balance = get_balance(hT1);
    best_balance = balance;
    table = 1;
  //for ht2
    balance = get_balance(hT2);
    if(balance < best_balance)
    {
      best_balance = balance;
      table = 2; 
    } 
  //for hT3
   balance = get_balance(hT3);
    if(balance < best_balance)
    {
      best_balance = balance;
      table = 3;
    } 
  
  //for hT4
   balance = get_balance(hT4);
    if(balance < best_balance)
    {
      best_balance = balance;
      table = 4;
    } 

  //for hT5
  balance = get_balance(hT5);
    if(balance < best_balance)
    {
      best_balance = balance;
      table = 5;
    } 

  //for hT6
  balance = get_balance(hT6);
    if(balance < best_balance)
    {
      best_balance = balance;
      table = 6;
    }    
    
    return table;
   }

// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");
    
	return hT1.size();
}
