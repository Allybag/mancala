#ifndef POS_H
#define POS_H
#include<iostream>    //std::cout
#include<string>  //std::string
#include<vector> //std::vector
#include<cctype> //isdigit()
struct pos
{
private:
	std::vector<int> position;

public:
	pos(const char*);
	bool firstToMove;
};
#endif
