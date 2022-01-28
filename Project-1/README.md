## Group members:

Ali Tahami: 📫 Atahami3@csu.fullerton.edu

Hamid Suha: 📫 hsuha@csu.fullerton.edu

Project 1

CPSC 335 - Algorithm Engineering

Fall 2021

Instructors: Doina Bein (dbein@fullerton.edu)

## Implementing algorithms

- The lawnmower algorithm
- The alternate algorithm

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## The lawnmower algorithm

It starts with the leftmost disk and proceeds to the right until it reaches the rightmost disk: compares every two adjacent disks and swaps them only if necessary. Now we have two light disks at the left-hand end and two dark disks at the right-hand end. Once it reaches the right-hand end, it starts with the rightmost disk, compares every two adjacent disks and proceeds to the left until it reaches the leftmost disk, doing the swaps only if necessary. The lawnmower movement is repeated ⌈n/2⌉ times.

Consider the example below when n=4, and the first row is the input configuration, the second row is the end of comparison from left to right, the third row is the end of the first run (round trip that contains left to right followed by right to left), etc.. The exact list of disks changes as follows at the end of each run (we consider a run to be a check of adjacent disks from left-to-right or right-to-left)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## The alternate algorithm

It starts with the leftmost disk and proceeds to the right until it reaches the rightmost disk: compares every two adjacent disks and swaps them only if necessary. It does not iterate through each index, but iterates over each pair (i.e., it moves 2 steps at a time). We consider a run to be a check of adjacent disks from left-to-right.

Next it starts with the second leftmost disk and proceeds to the right until it reaches the second rightmost disk: compares every two adjacent disks and swaps them only if necessary. This is the end of Run 2. Now we have two light disks at the left-hand end and two dark disks at the right-hand end. Next it is Run 3 that proceeds exactly as Run 1, starting with the leftmost disk. Run 3 is followed by Run 4 that is exactly as Run 2, starting with the second leftmost disk. So really, Run 1 and Run 2 continually alternate until sorting has finished. There are a total of n+1 runs.

Consider the example below when n=4, and the first row is the input configuration, the second row is the end of run 1, the third row is the end of run 2, etc..

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
## Implementation

provided with the following files.

disks.hpp is a C++ header that defines functions for the two algorithms described above. There are also classes that represent the input and output of the alternating disk problem. The function definitions are incomplete skeletons; you will need to rewrite them to actually work properly.
disks_test.cpp is a C++ program with a main() function that performs unit tests on the functions defined in disks.hpp to see whether they work, prints out the outcome, and calculates a score for the code. You can run this program to see whether your algorithm implementations are working correctly.
rubrictest.hpp is the unit test library used for the test program; you can ignore this file.
README.md contains a brief description of the project, and a place to write the names and CSUF email addresses of the group members. You need to modify this file to identify your group members.

END
