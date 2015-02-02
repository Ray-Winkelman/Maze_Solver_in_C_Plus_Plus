#include "Solver.h"

void Solver::Solve(Maze *maze){

	// Adding the entrance Coordinates to the stack.
	stack.Push(Coordinates(maze->GetEntrance()[0], maze->GetEntrance()[1]));
	maze->SetAt(stack.GetTop().GetX(), stack.GetTop().GetY());

	// While the current position is not the end of the maze.
	while(stack.GetTop().GetY() != maze->GetYLength() - 2){

		// While a move is available.
		if(MoveAvailible(stack.GetTop().GetX(), stack.GetTop().GetY(), maze)){

			// Advance through the maze.
			TakeMove(stack.GetTop().GetX(), stack.GetTop().GetY(), maze);

			// Drop a poison pill to indicate you've been there.
			maze->SetAt(stack.GetTop().GetX(), stack.GetTop().GetY());

			// If the position has returned to the entrance, the maze is not solvable.
		} else if(stack.GetTop().GetX() == maze->GetEntrance()[0] && 
			stack.GetTop().GetY() == maze->GetEntrance()[1]){
				throw ImpossibleMazeException("The maze does not have a clear path to an exit.");

		// If there's no moves, reduce the stack and backtrack.
		} else {
			stack.Pop();
		}		
	}

	// Create the solved maze. 
	maze->CreateSolvedMaze(&stack);
}

bool Solver::MoveAvailible(int x, int y, Maze * maze){
	try {

		if(x > 0 && maze->GetAt(x - 1, y) == ' '){
			return true;
		} else if (x < maze->GetXLength() && maze->GetAt(x + 1, y) == ' '){
			return true;
		} else if (y > 0 && maze->GetAt(x, y - 1) == ' '){
			return true;
		} else if (y < maze->GetYLength() && maze->GetAt(x, y + 1) == ' '){
			return true;
		}

	} catch(...){
		throw OutOfBoundsException("Attempted to read elements outside the bounds of the Maze array.");
	}
	return false;
}

void Solver::TakeMove(int x, int y, Maze * maze){
	if(x > 0 && maze->GetAt(x - 1, y) == ' '){
		stack.Push(Coordinates(x - 1, y));
	} else if (x < maze->GetXLength() && maze->GetAt(x + 1, y) == ' '){
		stack.Push(Coordinates(x + 1, y));
	} else if (y > 0 && maze->GetAt(x, y - 1) == ' '){
		stack.Push(Coordinates(x, y - 1));
	} else if (y < maze->GetYLength() && maze->GetAt(x, y + 1) == ' '){
		stack.Push(Coordinates(x, y + 1));
	} else {
		throw FalsePositiveException("Solver::MoveAvailible returned a false positive.");
	}
}