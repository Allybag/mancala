#ifndef game_H
#define game_H
#include<iostream>    //std::cout
#include<string>  //std::string
#include<vector> //std::vector
#include<cctype> //isdigit()

struct slot {
	int count;
	int mancala; // 0: No, 1: First, 2: Second
	slot* next;
	slot* prev;
};

class game {
	// game will basically be a cyclic linked list
	// keeping pointers to both mancalas, as well
	// as knowing who is to play
public:
	game(const char*);
	int playerToMove;
	int getScore() { return (firstMancala->count - secondMancala->count); }
	void print();
	void move(int);
	// Current plan:
	// Iterate through the char*, creating n slots,
	// storing pointers to both mancalas, and set
	// tail->next to be firstMancala (Logic muddled)


private:
	slot* firstMancala;
	slot* secondMancala;
	std::vector<slot> slotVec;
};
#endif