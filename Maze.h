#pragma once
#include "Stack.cpp"
#include <fstream>
using namespace std;

class Maze
{
private:
	int lines, linelength;
	const int *entrance;
	char **maze, **solved_maze;

public:
	Maze(const int* entrance, const string& path);
	void SetAt(int x, int y);
	char GetAt(int x, int y);	
	int GetXLength();
	int GetYLength();
	const int *GetEntrance();
	char GetSolvedMazeAt(int x, int y);
	void CreateSolvedMaze(Stack *stack);
	void SaveSolvedMaze(const char* inputfile, const char* outputfile);
};