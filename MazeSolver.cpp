/**
Name: Ethan Sam
Date: 10/25/2018
Project: 4
This project reads a file ifstream and returns a solution
*/
#include <fstream>
#include <iostream> 
#include "MazeSolver.h"


//This is our constructor
MazeSolver::MazeSolver(std::string input_file){
	std::ifstream inputStream;
	inputStream.open(input_file);
	if(!inputStream)
	{
		std::cerr << "Cannot read from input_file_name" << std::endl;
		exit(1);
	}
	else
	{
		inputStream >> maze_rows_ >> maze_columns_;
	initializeMaze(maze_rows_, maze_columns_);
	fillMaze(inputStream);
	initializeSolution();
	maze_ready = true;
	}
	
	
	inputStream.close();
}// END CONSTRUCTOR - FINISHED AS FAR AS IM CONCERNED
/**
The destructor is responsible for deallocating the memory that has been dynamically
allocated to the two matrices (maze_ and solution_ ).
Keep in mind that there could be instances in which the maze_ and solution_ were
never allocated (e.g. if the input cannot be read), so the destructor needs to check
that. 

Never allocated as in
*/

//We must consider if we canopen it 
MazeSolver::~MazeSolver(){
	
if((maze_!=nullptr)&&(solution_!=nullptr)){
		
		for( int i =0 ; i< maze_rows_ ; ++i){
			delete[] maze_[i];
			delete[] solution_[i];
		}
		delete[] maze_;
		delete[] solution_;
	}
	
}//CHECK LATER: POSSIBLY CHECK IF EDGE CASES ARE MET 
	


bool MazeSolver::mazeIsReady(){ 
	 return maze_ready;
}
 
 bool MazeSolver::solveMaze(){
/**
 While the stack is not empty X
 If your current position is an exit ($) X
 Print “Found exit!!!” and return true X
 Else if the current position is extensible X
 Push all positions reachable by moving one step SOUTH and one X
step EAST from the point on which you are standing on the stack. X
Mark you current position as PATH ( > ) on the solution X
Move forward by setting the current position to the one at the X
top of the stack. X
 Else (if you cannot move forward) X
Mark your current position as VISITED (X) on the maze X
Mark your current position as BACKTRACKED (@) on the solution X
Pop the stack //BACKTRACK STEP X
If the stack is not empty X
Move forward by setting the current position to the one at X
the top of the stack. X
 Else (if the stack is empty)
Print “This maze has no solution.” and return false
	 
	*/

Position startPosition;
startPosition.row = 0;
startPosition.column = 0;

	
while(!backtrack_stack_.empty())
{
	if(maze_[startPosition.row][startPosition.column]=='$')
	{
		std::cout << "Found exit!!!"<< std::endl;
		return true;
	}
	else if(extendPath(startPosition)) //canExtend returns a boolean, but it also pushes viable moves onto the stack
	{//Instead of doing this, we can overload the == operator to compare startPosition and getNewPosition
	
		solution_[startPosition.row][startPosition.column] = '>';
		startPosition.row = backtrack_stack_.top().row;
		startPosition.column = backtrack_stack_.top().column;
	}
	else
	{	
	maze_[startPosition.row][startPosition.column] = 'X';
	solution_[startPosition.row][startPosition.column]	 = '@';
	backtrack_stack_.pop();//delete the topmost element
	}
	
	if(!backtrack_stack_.empty())
	{
		startPosition.row = backtrack_stack_.top().row;
		startPosition.column = backtrack_stack_.top().column;
	}
	else
	{
		std::cout << "This maze has no solution." << std::endl;
		return false;
	}
	}
	return false;
 }
  
 void MazeSolver::printSolution(){
    if(solveMaze())
    {
        std::cout << std::endl << "The solution for this maze is:" << std::endl;

        for(int i=0; i<maze_rows_; i++)
        {
            for(int j=0; j<maze_columns_; j++)
            {
                std::cout << " ";
                std::cout << solution_[i][j];
            }
        }
    }
}
	 
 
 //Preference over South then east
 
 //PRIVATE MEMBER FUNCTIONS (helper functions)
    
    //pre: rows and columns are positive integers
    //post: allocates maze_ with rows and columns
    //called by constructor
    void MazeSolver::initializeMaze(int rows, int columns){
    //first step - open the file and error check
    if(rows > 0 && columns > 0)
    {
        maze_ = new char *[rows];
        for(int i =0; i< rows; i++)
        {
            maze_[i] = new char[columns];
        }
    }

    std::cout << maze_rows_ << std::endl;
    std::cout << maze_columns_ << std::endl;
} //END initializeMaze
		
    
    //pre: maze_ has been allocated with the correct number of rows and columns read from input file
    //post: fills in maze_ with characters read from input file
    //called by constructor
    void MazeSolver::fillMaze(std::ifstream& input_stream) {
	// We allocate the dynamic array which is an array of pointers, 
	//where each pointer  points to the memory location of an array
	
	
	maze_ = new char *[maze_rows_]; //We allocate the dynamic array
	for (int i=0; i<maze_rows_; i++)
	{
		maze_[i]= new char[maze_columns_];
	}
		for (int r=0; r<maze_rows_; ++r) 
		{
			for (int c = 0; c<maze_columns_; ++c)
			{
				input_stream >> maze_[r][c]; //We fill the Maze from the .txt 
			}	
		}
	
	}//END fillMaze FILLED!

    
    //pre: maze_ has been initialized with valid character values in {'_', '*','$'}
    //     start position is always [0][0]
    //post: initializes solution_ with a copy of maze_
    //      initializes backtrack_stack_  with all viable paths from position [0][0]
    //      and mark current position as visited ( > ) on solution_
    //called by constructor
    void MazeSolver::initializeSolution(){
    Position start_position;
    start_position.row = 0;
    start_position.column = 0;
    if(mazeIsReady()){
        copyMazetoSolution();
	}
    if(extendPath(start_position))
    {
        solution_[start_position.row][start_position.column] = '>';
        //std::cout << solution_[start_position.row][start_position.column];
    }
}//Does this need to change maze_ as well? ANSWER NO
				
	
    
    //pre: maze_ has been properly initialized
    //post: allocates solution_ to the correct number of rows and columns
    //      and copies the contents of maze_ into solution_
    //called by initializeSolution()
    void  MazeSolver::copyMazetoSolution(){
	solution_ = new char *[maze_rows_]; //We allocate the dynamic array
	for (int i=0; i<maze_rows_; ++i)
	{
		solution_[i]= new char[maze_columns_];
	}
	
	for (int r=0; r<maze_rows_; ++r) 
		{
			for (int c = 0; c<maze_columns_; ++c)
			{
				solution_[r][c] = maze_[r][c];  //We copy the elements from maze_ into solution_
			}	
		}
	
	
    }
	/**	
	extendPath will use helper functions:
	Position getNewPosition(Position old_position, direction dir);
	bool isExtensible(Position current_position, direction dir); 
*/	
    //pre: current_position is a valid position on the maze_
    //post: adds all positions extensible from current_position to backtrack_stack_
    //return: true if path was extended, false otherwise
    //called by solveMaze()
    bool MazeSolver::extendPath(Position current_position){
		
		Position newPosition; //Create a new reference to position
		
		bool canExtend = false;
		
		if(isExtensible(current_position, SOUTH))//ORDER MATTERS FOR THE PROJECT, CHECK SOUTH BEFORE EAST
		{
			newPosition = getNewPosition(current_position, SOUTH);
			backtrack_stack_.push(newPosition);
			solution_[newPosition.row][newPosition.column] = '>';
			canExtend = true;
		}
		if(isExtensible(current_position, EAST))
		{
			newPosition = getNewPosition(current_position, EAST);
			backtrack_stack_.push(newPosition);
			solution_[newPosition.row][newPosition.column] = '>';
			canExtend = true; 
		}
		
		return canExtend;//if 2, include the last one, if one, just include it 
}
		
    
    //pre: old_position is a Position initialized with row and column to valid positions in maze_ and it is extensible in direction dir
    //return: a new Position on the maze moving in direction dir from old_position
    //called by extendPath()
    Position MazeSolver::getNewPosition(Position old_position, direction dir){
		Position newPosition;
		
		if(dir==SOUTH){
		newPosition.row = old_position.row+1;
		newPosition.column = old_position.column; 
		}
		if(dir==EAST){
		newPosition.column = old_position.column+1;
		newPosition.row = old_position.row;
		}
		
	return newPosition;//We update the new position
	}
			
		
    
    //checks if the path can be extended in maze_ from position current_position in direction dir
    //return: true if path can be extended given current_position and dir, false otherwise
    //called by extendPath
    bool MazeSolver::isExtensible(Position current_position, direction dir){
		
		
	if((current_position.row>=0&&current_position.row < maze_rows_)&&(current_position.column>=0&&current_position.column<maze_columns_))
	{		
		if(dir==SOUTH){
			
			if(maze_[current_position.row+1][current_position.column] != '*')//We check if south is a wall
			{	
				return true; //Check for X as well
			}
		}
		if(dir==EAST){
			
			if(maze_[current_position.row][current_position.column+1] != '*')//We check if east is a wall
			{
				return true;
			}
		}
			
	}
	return false;
}
    