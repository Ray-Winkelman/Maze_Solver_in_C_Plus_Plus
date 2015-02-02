#pragma once
class Coordinates
{
private:
	int x, y;
public:
	Coordinates(){
		this->x = 0;
		this->y = 0;
	}

	Coordinates(int x, int y){
		this->x = x;
		this->y = y;
	}

	Coordinates(const Coordinates& other){
		this->x = other.x;
		this->y = other.y;
	}

	int GetX(){
		return x;
	}

	int GetY(){
		return y;
	}
};