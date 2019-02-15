/**
Name: Ethan Sam
Date: 11/05/2018
Project: 4
This project reads a file ifstream and returns a solution
*/
//  MazeSolver.cpp
//
//  Maze:
//  This class finds a solution to a maze read from an input file
//  and prints a solution to the standard output


#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <stack>
#include <cctype>
#include "MazeSolver.h"

MazeSolver::MazeSolver(std::string input_file) 
{
  std::ifstream file;
  file.open(input_file);
  if (file.fail()) {
    std::cerr << "Cannot read from file. Exit\n";
    exit(1);
  }
  
  file >> maze_rows_  >> maze_columns_;
  initializeMaze(maze_rows_, maze_columns_);
  if (mazeIsReady()) {
    fillMaze(file);
    initializeSolution();
    Position pos; // push starting pos ([0][0]) into stack
    pos.row = 0;
    pos.column = 0;
    backtrack_stack_.push(pos);
  }
  file.close();
}

/**
The destructor is responsible for deallocating the memory that has been dynamically
allocated to the two matrices (maze_ and solution_ ).
Keep in mind that there could be instances in which the maze_ and solution_ were
never allocated (e.g. if the input cannot be read), so the destructor needs to check
that. 

*/

MazeSolver::~MazeSolver() 
{
  for (int i = 0; i < maze_rows_; i++)//Iterate and delete every maze_[] and solution_[] item 
  {
    delete[] maze_[i];
	delete[] solution_[i];
  }
  delete[] maze_;
  delete[] solution_;

}//END ~MazeSovler

bool MazeSolver::mazeIsReady() {
  if (maze_rows_ > 0 && maze_columns_ > 0) 
	{
     maze_ready = true;
	}
	
  return maze_ready;
  
}//END mazeIsReady

void MazeSolver::initializeMaze(int rows, int columns) 
{
  /* Note: A dynamic array is an array data structure that can be
    resized and which allows elements to be added or removed.
	
	Also, a dynamic array is an array of pointers that each point to an array (memory location)
  */
  
  //In order to initialize the maze, we need to set the private member variables maze_rows_ and maze_columns_ to rows and columns
  maze_rows_ = rows; 
  maze_columns_ = columns;
  
  maze_ = new char *[maze_rows_]; // We create a dynamic array (of Size maze_rows_) full of pointers (nullptr)
  for (int i = 0; i < maze_rows_; i++) 
  {
    maze_[i] = new char[maze_columns_]; // We iterate through each item in the dynamic array and set each to a new array
  }
}

void MazeSolver::fillMaze(std::ifstream& input_stream) 
{
  for (int r=0; r<maze_rows_; ++r) 
	{
		for (int c = 0; c<maze_columns_; ++c)
		{
		input_stream >> maze_[r][c]; //We fill the Maze from the .txt 
		}	
	}
}

bool MazeSolver::isExtensible(Position currentPositionition, direction dir) 
{
	
	bool canExtend = false;
  if (dir == SOUTH && (currentPositionition.row+1 < maze_rows_)) 
  { 
	if (maze_[currentPositionition.row+1][currentPositionition.column] == '_'|| maze_[currentPositionition.row+1][currentPositionition.column] == '$')
	{
       canExtend = true;
    }
  }
  if (dir == EAST && (currentPositionition.column+1 < maze_columns_))
	  { // making sure im within the matrix
    if (maze_[currentPositionition.row][currentPositionition.column+1] == '_'|| maze_[currentPositionition.row][currentPositionition.column+1] == '$') 
	{
       canExtend = true;
    }
  }
  return canExtend;
}

bool MazeSolver::extendPath(Position currentPositionition) 
{
  bool canExtend = false;
  if (isExtensible(currentPositionition, SOUTH)) 
  {
    backtrack_stack_.push(getNewPosition(currentPositionition, SOUTH));
    canExtend = true;
  }
  if (isExtensible(currentPositionition, EAST))
  {
    backtrack_stack_.push(getNewPosition(currentPositionition, EAST));
    canExtend = true;
  }
  return canExtend;
}

Position MazeSolver::getNewPosition(Position old_position, direction dir) 
{
  Position newPosition;
  if (dir == SOUTH && (old_position.row+1 < maze_rows_))
	  {
	  newPosition.row = old_position.row + 1; // move south
	  newPosition.column = old_position.column;
  }
  if (dir == EAST && (old_position.column+1 < maze_columns_))
	  { // within matrix
   newPosition.row = old_position.row;
   newPosition.column = old_position.column + 1; // move east
  }
  return newPosition;
}

bool MazeSolver::solveMaze()
 {
	Position currentPosition;
	currentPosition.row = backtrack_stack_.top().row;
	currentPosition.column = backtrack_stack_.top().column;
	
	while (!backtrack_stack_.empty()) 
	{
		if (maze_[currentPosition.row][currentPosition.column] == '$')
		{
      std::cout << "Found the exit!!!\n";
			return true;
		}
		else if (extendPath(currentPosition))	
		{
			solution_[currentPosition.row][currentPosition.column] = '>';
			currentPosition = backtrack_stack_.top(); // the top should be east if east was extensible
		}
		else if (!extendPath(currentPosition)) 
		{ // if it wasnt extinsible at all
			maze_[currentPosition.row][currentPosition.column] = 'X';
			solution_[currentPosition.row][currentPosition.column] = '@';
			backtrack_stack_.pop(); // backtracking
			if (!backtrack_stack_.empty()) 
			{
				currentPosition = backtrack_stack_.top(); // Moved forward by setting the current position to the one at the top of the stack.
			}
			else if (backtrack_stack_.empty()) 
			{ // if we can't move forward at all
				std::cout << "This maze has no solution.\n";
				return false;
			}
		}
	}
	return true;
}

void MazeSolver::printSolution() 
{
  std::cout << "The solution to this maze is:\n";
  for (int i = 0; i < maze_rows_; i++) 
  {
    for (int j = 0; j < maze_columns_; j++)
		{
      std::cout << solution_[i][j] << " ";
    }
    std::cout << std::endl; // at the end of iterating through the columns to form a row, skip a line to start the next row
  }
}

void MazeSolver::copyMazetoSolution() 
{
  // initializing solution_ with a copy of maze_
  for (int i = 0; i < maze_rows_; i++) 
  {
    for (int j = 0; j < maze_columns_; j++)
	{
      solution_[i][j] = maze_[i][j];
    }
  }
}

void MazeSolver::initializeSolution() 
{
  // 2D Array of solution
  solution_ = new char *[maze_rows_]; // dynamic array (size rows) of pointers to chars
  for (int i = 0; i < maze_rows_; i++) 
  {
    solution_[i] = new char[maze_columns_]; // each i-th pointer is now pointing to dynamic array (size cols) of actual char values
  }
  copyMazetoSolution(); // 2D array for solution and copies maze to solution
}