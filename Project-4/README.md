## Group members:

Ali Tahami: 📫 Atahami3@csu.fullerton.edu

Hamid Suha: 📫 hsuha@csu.fullerton.edu

Project 4

CPSC 335 - Dynamic vs. Exhaustive

Fall 2021

Instructors: Doina Bein (dbein@fullerton.edu)

## Implementing algorithms

- The Exhaustive Optimization Algorithm
- The Dynamic Programming Algorithm

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Abstract
In this project we will implement two algorithms that both solve the crane unloading problem. The first algorithm uses exhaustive optimization and takes exponential time. The second algorithm uses dynamic programming, and takes cubic time. 

The Problem
Both algorithms will be used to solve another interesting problem related to containers and loading them into ships. Suppose that you have arrived at the seaport and need to navigate among buildings to reach various cranes that will take your containers and load them into various ships. 

Each truck is allowed to follow only one route and it can drive only south or east, but cannot drive north nor west. We will represent the seaport driveable area as a 2D grid, like the following.
seaport driveable area as a 2D grid:

<img width="180" alt="Screen Shot 2021-12-02 at 8 25 57 PM" src="https://user-images.githubusercontent.com/89944617/144545075-4ae4470b-1890-43cb-8ff8-1a9276c5ed33.png">

A truck starts at row 0 and column 0, i.e. coordinate (0, 0), at the top-left corner. Each c cell represents a crane, each X represents a building, and each . cell represents a passable space. A truck’s goal is to plan a route for driving that maximizes the number of cranes that can be reached, while avoiding buildings.

Here is an optimal solution for the previous grid:

<img width="177" alt="Screen Shot 2021-12-02 at 8 27 38 PM" src="https://user-images.githubusercontent.com/89944617/144545216-7581b73b-37a5-461c-9cdd-16725090d81f.png">

In this diagram, the + cells represent passable space that the truck drove through, and the capital C cells represent cranes that the truck reached and had cargo unloaded. A . still represents passable space that was never visited, and lower-case c still represents cranes that were neither reached nor used. Observe that the path starts at (0, 0), and moves east and south, but not in any other direction. Also note that there is no valid path in this grid that would reach more than 7 cranes.

We can define this puzzle as an algorithmic problem.

| Crane unloading problem |
| -- |
|input: a r⨉c matrix G where each cell is one of . (passable), c (crane), or X (building); and G[0][0]= 
output: a path starting at (0, 0); where each step is either a start, move east, or move south; that does not visit any X cell; and the number of c cells along the path is maximized |

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## The Exhaustive Optimization Algorithm

Our first algorithm solving the crane unloading problem is exhaustive. The output definition says that the number of cranes reached must be maximized, so this is an exhaustive optimization algorithm (not exhaustive search).

Since all paths start at (0, 0) and the only valid moves are east and south, paths are never west or north. So the longest possible path is one that reaches the bottom-right corner of the grid. The grid has r rows and c columns, so this longest path involves (r-1) down moves and (c-1) right moves, for a total of
r + c - 2 moves.

There are two kinds of moves, east → and south ↓. Coincidentally there are two kinds of bits, 0 and 1. So we can generate move sequences by generating bit strings, using the same method that we used to generate subsets in section 7.5 of the ADITA textbook. We loop through all binary numbers from 0 through 2n-1, and interpret the bit at position k as the east/south step at index k.

A candidate path is valid when it follows the rules of the crane unloading problem. That means that the path stays inside the grid, and never crosses a building (X) cell.

Combining these ideas gives us a complete and clear algorithm.


Hint:
Let n = max(r, c). Then maxlen ∈ O(n), the outermost for loop repeats O(n) times, the middle for loop over bits repeats O(2n) times, and the inner for loops repeat O(n)times, and the total run time of this algorithm is O(n22n). This is a very slow algorithm.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## The Dynamic Programming Algorithm

This problem can also be solved by a dynamic programming algorithm. This dynamic programming array A stores partial solutions to the problem. In particular,

A[r][c] = the crane-maximizing path that starts at (0, 0) and ends at (r, c); or None if (r, c) is unreachable

Recall that in this problem, some cells are occupied by buildings and are therefore to be avoided by trucks.

The base case is the solution for A[0][0], which is the trivial path that starts and takes no subsequent steps.

A[0][0] = [start]

We can build a solution for a general case based on pre-existing shorter paths. Trucks can only drive east and south. So there are two ways a truck path could reach (i, j).
The truck path above (i, j) could add a southward step.
The truck path to the left of (i, j) could add an eastward step.
The algorithm should pick whichever of these two alternatives is optimal, which in this problem means whichever of the two candidate paths reach more cranes.

However, neither of these paths is guaranteed to exist. The from-above path (1) only exists when we are not on the top row (so when i>0), and when the cell above (i, j) is not a building. Symmetrically, the from-west path (2) only exists when we are not on the leftmost column (so when j>0) and when the cell left of (i, j) is not a building

Finally, observe that A[i][j] must be None when G[i][j]==X, because a path to (i, j) is only possible when (i, j) is not a building.


Hint:
The time complexity of this algorithm is dominated by the general-case loops. The outer loop repeats n times, the inner loop repeats n times, and creating each of from_above and from_left takes O(n) time to copy paths, for a total of O(n3) time. While O(n3) is not the fastest time complexity out there, it is polynomial so considered tractible, and is drastically faster than the exhaustive algorithm.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Implementation

provided with the following files.


1. cranes_algs.hpp is a C++ header that defines two functions, one for each of the algorithms defined above. These function bodies are marked TODO and your assignment is to fill them in with algorithm implementations.
1. cranes_types.cpp is a C++ header that defines data types for the grids, paths, and related objects for the crane unloading problem. This code is complete; you should not modify this file.
1. cranes_timing.cpp is a C++ program with a main() function that measures one experimental data point for each of the algorithms. You can expand upon this code to obtain several data points for each of your algorithm implementations.
1. Makefile, cranes_test.cpp, timer.hpp, rubrictest.hpp, and README.md work the same way as in prior projects.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Required Steps:
- [x] Analyze your dynamic programming algorithm code mathematically to determine its big-O efficiency class, probably O(n2) or O(n n).
- [x] Analyze your exhaustive optimization algorithm code mathematically to determine its big-O efficiency class, probably O(2nn).
- [x] Gather empirical timing data by running your implementations for various values of n.
- [x] Draw a scatter plot for each algorithm and fit line for your timing data. The instance size nshould be on the horizontal axis and elapsed time should be on the vertical axis. Each plot should have a title; and each axis should have a label and units of measure.
- [x] Conclude whether or not your empirically-observed time efficiency data is consistent, or inconsistent, with your mathematically-derived big-O efficiency class for each algorithm.


for more detail:
https://docs.google.com/document/d/1JPHV4frgw_g3tmO8LujClVzDdzNUIj4ViDzQk4Y9zt8/edit#

END
