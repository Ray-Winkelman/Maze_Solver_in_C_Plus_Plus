#pragma once
#include "Coordinates.cpp"
#include "Exceptions.cpp"
#include <cstring>
#include <iostream>
using namespace std;

class Stack
{
private:
	int size;
	Coordinates * array;
public:
	Stack()
	{
		size = 0;
		array = new Coordinates[size];
	}

	void Push(Coordinates item)
	{
		size++;

		Coordinates * newArr = new Coordinates[size];
		memcpy(newArr, array, size * sizeof(Coordinates));

		delete[] array;
		array = newArr;
		array[size - 1] = Coordinates(item);
	}

	void Pop()
	{
		size--;

		if(size < 0){
			throw StackUnderflowException("Stack underflow exception. Back-tracked out of bounds.");
		}

		Coordinates * newArr = new Coordinates[size];
		memcpy(newArr, array, size * sizeof(Coordinates));

		delete[] array;
		array = newArr;
	}

	Coordinates GetTop()
	{
		return array[size - 1];
	}

	int GetSize(){
		return size;
	}

	// For debugging only.
	void PrintCoordinatesList()
	{
		for(int i = 0; i < 10; i++){
			cout << this->array[i].GetX() << ", " << this->array[i].GetY() << endl;
		}
	}
};