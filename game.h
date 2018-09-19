#ifndef game_H
#define game_H
#include<iostream>    //std::cout
#include<string>  //std::string
#include<vector> //std::vector
#include<cctype> //isdigit()

class game {
	// game will basically be a cyclic linked list
	// keeping pointers to both mancalas, as well
	// as knowing who is to play
public:
	void accept(const char*);
	std::vector<int> listMoves();
	int playerToMove;
	void print();
	void move(int);
	// Current plan:
	// Iterate through the char*, creating n slots,
	// storing pointers to both mancalas, and set
	// tail->next to be firstMancala (Logic muddled)


private:
	std::vector<int> slotVec;
	std::vector<int> mancalaSlots;
};
#endif
