///////////////////////////////////////////////////////////////////////////////
// cranes_algs.hpp
//
// Algorithms that solve the crane unloading problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crane_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>

#include "cranes_types.hpp"

namespace cranes {

// Solve the crane unloading problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path crane_unloading_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  // TODO: implement the exhaustive search algorithm, then delete this
  // comment.

  path best(setting);

  for (size_t steps = 1; steps <= max_steps; ++steps)// start with this 
  {
    uint64_t mask = uint64_t(1) << steps;
    for (uint64_t bits = 0; bits < mask; ++bits)
    {

      path candidate(setting);
     // bool valid = true;
      // add to candidate a path not exceedings <steps> binary values


      for( uint64_t k = 0; k < steps; ++k)//sc=n+1
      {
        int bit;//0
        bit = (bits >> k) & 1;//sc=3
        
        if(bit == 1)//if bit is 1 move right sc= 1+max(0,0) = 1
        {
          //if bit is 1 candidate stays inide cell so never hits X
          if(candidate.is_step_valid(STEP_DIRECTION_EAST))//sc=0
            {
              //moves to new position(right)
              candidate.add_step(STEP_DIRECTION_EAST);
            }
        }
            else
            {
              //if bit is 0 candidate stays inide cell so never hits X
              if(candidate.is_step_valid(STEP_DIRECTION_SOUTH))//sc=0
              {
                //moves to new position(down)
                candidate.add_step(STEP_DIRECTION_SOUTH);
              }
            }

      }
          
      if (candidate.total_cranes() > best.total_cranes()) {//sc=1+max(1,0) = 2
        best = candidate;
      }
    }
  }
  //std::cout<<std::endl;
  //best.print();
  return best;//sc=0
}

// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
path crane_unloading_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.

  using cell_type = std::optional<path>;

  std::vector<std::vector<cell_type>> A(setting.rows(),
                                        std::vector<cell_type>(setting.columns()));

  A[0][0] = path(setting);//new matrix
  assert(A[0][0].has_value());

  for (coordinate r = 0; r < setting.rows(); ++r)// start here 
  {
    for (coordinate c = 0; c < setting.columns(); ++c) 
    {
      // set the value for A[r][c] as a path collecting most cranes
      //if we dont hit a wall
      if (setting.get(r, c) != CELL_BUILDING) 
        {
          //from_above = from_left = None
          std::optional<path> from_above;
          std::optional<path> from_left;
          //if i > 0 and A[i-1][j] is not None
          if(r > 0 && A[r-1][c].has_value())
            {
              //from_above = A[i-1][j] + down
              from_above = A[r-1][c];
              if(from_above->is_step_valid(STEP_DIRECTION_SOUTH))
                {   
                 from_above->add_step(STEP_DIRECTION_SOUTH);
                }
            }
            //if i > 0 and A[i][j-1] is not None
          if(c > 0 && A[r][c-1].has_value())
           {
             //from_left = A[i][j-1] + right
              from_left = A[r][c-1];
              if(from_left->is_step_valid(STEP_DIRECTION_EAST))
                {
                 from_left->add_step(STEP_DIRECTION_EAST);
                }
           }
          if(from_above.has_value() && from_left.has_value())
            {
              if(from_above->total_cranes() > from_left->total_cranes())
                { 
                   A[r][c] = from_above;
                }   
              else
                {
                  A[r][c] = from_left;
                }
            }
          else if(from_above.has_value())
                {
                  A[r][c] = from_above;
                }
          else if(from_left.has_value())
                { 
                  A[r][c] = from_left;
                }
      }
    }
  }
// close } soemwehere here or above

  cell_type* best = &(A[0][0]);
  assert(best->has_value());
  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {
      if (A[r][c].has_value() && A[r][c]->total_cranes() > (*best)->total_cranes()) {
        best = &(A[r][c]);
      }
    }
  }

  assert(best->has_value());
 //   std::cout << "total cranes" << (**best).total_cranes() << std::endl;
//std::cout<<std::endl;
//(**best).print();
  return **best;
}


}
