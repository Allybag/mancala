#ifndef game_H
#define game_H
#include<iostream>    //std::cout
#include<string>  //std::string
#include<vector> //std::vector
#include<cctype> //isdigit()

class game {
public:
	void accept(const char*);
	std::vector<int> listMoves();
	int playerToMove;
	void print();
	void move(int); // May not end turn (final slot drops in mancala)
	int score() { return slotVec[mancalaSlots[1]] - slotVec[mancalaSlots[2]]; };

private:
	std::vector<int> slotVec;
	std::vector<int> mancalaSlots;
};
#endif
