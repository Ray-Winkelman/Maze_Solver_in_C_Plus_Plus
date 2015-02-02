#include <string>

class OutOfBoundsException: public std::runtime_error{
public:
	OutOfBoundsException(std::string msg):runtime_error(msg.c_str()){}
};

class ImpossibleMazeException: public std::runtime_error{
public:
	ImpossibleMazeException(std::string msg):runtime_error(msg.c_str()){}
};

class StackUnderflowException: public std::runtime_error{
public:
	StackUnderflowException(std::string msg):runtime_error(msg.c_str()){}
};

class FileTypeException: public std::runtime_error{
public:
	FileTypeException(std::string msg):runtime_error(msg.c_str()){}
};

class FalsePositiveException: public std::runtime_error{
public:
	FalsePositiveException(std::string msg):runtime_error(msg.c_str()){}
};