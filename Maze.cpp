#include "Maze.h"

Maze::Maze(const int* entrance, const string& path):lines(0), linelength(0), entrance(entrance)
{
	ifstream inStream;
	char templine[1024];	

	try{
		inStream.open(path, std::fstream::in);
	} catch (...){
		throw FileTypeException("Corrupt file, or incorrect filename.");
	}

	// Getting the line length,
	// and the total number of lines.
	while (!inStream.eof())
	{
		try{
			inStream.getline(templine, 1024);
		} catch (...){
			throw FileTypeException("Can't read line: " + to_string(lines) + " of the text file.");
		}

		lines++;
	}

	// Getting the length of the rows.
	linelength = strlen(templine) + 1;

	// Returning to the beginning of the file. 
	inStream.clear();
	inStream.seekg(0, ios::beg);

	// Allocating memory for the elements.
	maze = new char*[lines];
	solved_maze = new char*[lines];
	for(int i = 0; i < lines; i++){
		maze[i] = new char[linelength];
		solved_maze[i] = new char[linelength];
	}

	// Writing the file to the arrays.
	int x = 0;
	while (!inStream.eof())
	{
		inStream.getline(templine, 1024);
		strcpy(solved_maze[x], templine);
		strcpy(maze[x], templine);
		x++;
	}

	inStream.close();
}

char Maze::GetAt(int x, int y){
	return maze[x][y];
}

void Maze::SetAt(int x, int y){
	maze[x][y] = 'x';
}

int Maze::GetXLength(){
	return lines;
}

int Maze::GetYLength(){
	return linelength;
}

const int* Maze::GetEntrance(){
	return entrance;
}

void Maze::CreateSolvedMaze(Stack * stack){
	int coordinates = stack->GetSize();

	for(int i = 0; i < coordinates; i++){
		solved_maze[stack->GetTop().GetX()][stack->GetTop().GetY()] = 'x';
		stack->Pop();
	}
}

char Maze::GetSolvedMazeAt(int x, int y){
	return solved_maze[x][y];
}

void Maze::SaveSolvedMaze(const char* inputfile, const char* outputfile){

	wofstream outStream;

	try{
		outStream.open(outputfile);
	} catch (...){
		throw FileTypeException("Can't create the file.");
	}

	try{
		outStream << "Original: " << endl << inputfile << endl << endl;

		for(int x = 0; x < lines; x++){
			outStream << solved_maze[x] << endl;
		}
	} catch (...){
		throw FileTypeException("Can't write the solved maze to the file.");
	}
	outStream.close();
}