///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// Group Members:
// Ali Tahami: Atahami3@csu.fullerton.edu
// Hamid Suha: hsuha@csu.fullerton.edu
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include<cmath>

#include <functional>
#include <iostream>
using namespace std;

enum disk_color { DISK_LIGHT, DISK_DARK};

class disk_state {
private:
  std::vector<disk_color> _colors;//disk[]

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_initialized() const {

    for (size_t i = 0; i < _colors.size(); ++i)
    {
      if (i % 2 == 0 && _colors[i] == DISK_DARK) // light is even
        return false;
      else if (i % 2 == 1 && _colors[i] == DISK_LIGHT)  // dark is odd
        return false;
    }
      return true;
  }

  // Return true when this disk_state is fully sorted, with all light disks on 
  // the left (low indices) and all dark disks on the right (high indices).
  bool is_sorted() const {

      size_t half = _colors.size()/2;
      for(size_t i = 0; i < half;i++)
      {
        if(_colors[i] != DISK_LIGHT)
          return false;
      }
      for(size_t i = half; i <_colors.size();i++)
      {
        if(_colors[i] != DISK_DARK)
          return false;
      }
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;
  
public:
  
  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  const disk_state& after() const {
    return _after;
  }
  
  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
    unsigned count =0;
    size_t n = before.total_count()/2;// total count is _colors.size();
    disk_state place = before;

    for(size_t i =0; i< n+1;i++)
    {
      // iterate through even disks
      if(i % 2 == 0) 
      {
        for(size_t j = 0; j<= 2*n-1;j+=2)
        {
          // swap condition
          if(place.get(j) > place.get(j+1))
          {
            place.swap(j);
            count ++;
          }
        }
      }
      // iterate through odd disks
      else
      {
        for(size_t j = 1; j<2*n-2;j+=2)
        {
          // swap condition
          if(place.get(j) > place.get(j+1))
          {
            place.swap(j);
            count ++;
          }
        }
      }
    }
  // return count
  return sorted_disks(place, count);
}

// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
   
    unsigned count = 0;//type that it wants returned
    disk_state place = before;
    size_t n = before.total_count()/2; // Count of DISK_DARK and DISK_LIGHT
   
    for(size_t j =1; j<= ceil(n/2); j++)
    {
      // iterate from left to right
      for(size_t i = 0; i< 2*n-1; i++)
      {
        // swap condition
        if(place.get(i) > place.get(i+1))
        {
          place.swap(i);
          count ++;
        }
      }
      // iterate from right to left
      for(size_t i = 2*n-1;i > 1; --i)
      {     
        // swap condition
        if(place.get(i) < place.get(i-1))
        {
          place.swap(i-1);
          count ++;
        }
      }
    }
    // return the count
    return sorted_disks(place, count);
}



