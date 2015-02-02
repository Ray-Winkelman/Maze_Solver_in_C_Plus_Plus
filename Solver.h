#pragma once
#include "Stack.cpp"
#include "Coordinates.cpp"
#include "Maze.h"
using namespace std;
class Solver
{
private:
	Stack stack;
public:
	void Solve(Maze *maze);
	bool MoveAvailible(int x, int y, Maze * maze);
	void TakeMove(int x, int y, Maze * maze);
};

