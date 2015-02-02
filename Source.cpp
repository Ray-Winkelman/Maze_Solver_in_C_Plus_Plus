#include "Maze.h"
#include "Solver.h"
#include <conio.h>
#include <sys/stat.h>
#include <boost/regex.hpp>
using namespace boost;
using namespace std;

void Print(Maze *maze);
void PrintSolvedMaze(Maze *maze);
inline bool FileExists (const string& name);

/// <summary>
///
/// This program solves text file mazes by stacking coordinates, and writing to each location in the maze it has been.
/// It requires two arguments like so: maze.exe C:\Users\Ray\Desktop\Maze.txt C:\Users\Ray\Desktop\Solved_Maze.txt
/// 
/// Copyright © 2015 Ray Winkelman
/// </summary>
int main(int argc, char* argv[]){
	const static int entrance[2] = {1, 0};

	// Checking that the input filename is a valid filename, and a text file; before checking it exists.
	if(!regex_match(argv[1], regex("([a-z]|[A-Z]):\\\\(([a-z]|[A-Z]|[0-9]|[ ]|[_])+(\\\\))*([a-z]|[A-Z]|[0-9]|[ ]|[_])+\\.txt")) || !FileExists(argv[1])){
		cout << endl << "Invalid input file. It must be a full path to a text file." << endl;
		return 1;
	}

	// Checking that the output filename is a valid filename, and text file.
	if(!regex_match(argv[2], regex("([a-z]|[A-Z]):\\\\(([a-z]|[A-Z]|[0-9]|[ ]|[_])+(\\\\))*([a-z]|[A-Z]|[0-9]|[ ]|[_])+\\.txt"))){
		cout << endl << "Invalid output file. It must be a full path to a text file." << endl;
		return 1;
	}

	// Creating the maze, and a pointer to it.
	Maze maze(entrance, argv[1]);
	Maze *pointertomaze = &maze;

	// Creating the solver.
	Solver solver;

	// Attempting to solve the maze.
	// If the maze can't be solved, a custom, or system exception will be thrown.
	bool success = false;
	try {
		solver.Solve(pointertomaze);
		success = true;
	} catch(std::exception &e){
		cout << e.what() << endl;
		return 1;
	} 

	// If the maze was solved, print it to the console, and prompt to save.
	if(success){
		PrintSolvedMaze(pointertomaze);
		cout << endl << "Success!" << endl;
		cout << endl << "Enter 's' to save the solved maze. (Press any other key to skip)" << endl;


		// Save the maze.
		if(_getch() == 's'){
			try {
				maze.SaveSolvedMaze(argv[1], argv[2]);
			} catch(std::exception &e){
				cout << e.what() << endl;
				return 1;
			} 
			cout << endl << "The solved maze has been saved at: " << argv[2] << endl;
		}

		// Prompt to print to poison pill trail.
		cout << endl << "Press 'r' to print the poison pill trail, any other key to exit." << endl;

		// print the trail. 
		if(_getch() == 'r'){
			Print(pointertomaze);
			cout << endl << "Press any key to exit." << endl;
			_getch();
		}
	}
	return 0;
}

void Print(Maze *maze){
	for(int x = 0; x < maze->GetXLength(); x++)
	{
		for(int y = 0; y < maze->GetYLength(); y++)
		{
			cout << maze->GetAt(x, y);
		}
		cout << endl;
	}
}

void PrintSolvedMaze(Maze *maze){
	for(int x = 0; x < maze->GetXLength(); x++)
	{
		for(int y = 0; y < maze->GetYLength(); y++)
		{
			cout << maze->GetSolvedMazeAt(x, y);
		}
		cout << endl;
	}
}

inline bool FileExists(const string& name) {
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); 
}