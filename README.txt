In "inputA.txt" or "inputB.txt" 
_ = hallway

* = wall

$ = exit
--------------------------------
To change to "inputB.txt" open main.cpp and change the read file:
 MazeSolver solver("inputB.txt");

TO RUN:

Use a g++ compiler or any bash equivalent:

type in:

g++ -o myProg main.cpp

./myProg 


You can modify hallways and walls in any way, but starting position 
will be in the upper-left position and the exit will always be in
the lower-right position 



