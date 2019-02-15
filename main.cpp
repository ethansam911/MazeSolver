#include <iostream>
#include "MazeSolver.h"
#include "MazeSolver.cpp"

int main() {

 MazeSolver solver("inputB.txt");

 if(solver.mazeIsReady())
 {
 solver.solveMaze();

 solver.printSolution();
 }

 return 0;
}