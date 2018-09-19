#include "game.h"
#include <algorithm>
#define SLOTS 6


void game::accept(const char* recvBuff) {
	slotVec.clear();
	mancalaSlots.clear();
	int slotCount = 0;
	const char* recvChar = recvBuff;
	while (*recvChar)
	{
		if (*recvChar == ',')
		{
			slotVec.push_back(slotCount);
			slotCount = 0;
		} else if (isdigit(*recvChar)) {
			slotCount *= 10;
			slotCount += (*recvChar - '0');
		} else if (*recvChar == 'T') {
			playerToMove = 1;
			break;
		} else if (*recvChar == 'F') {
			playerToMove = 2;
			break;
		}
		++recvChar;
	}
	mancalaSlots.push_back(5); // Gibberish in position 1
	mancalaSlots.push_back(0); // Player 1 Mancala
	mancalaSlots.push_back(SLOTS + 1); // Player 2 Mancala
}

void game::print() {
	std::string outString;
	for (auto gameSlot: slotVec) {
		outString = outString + std::to_string(gameSlot) + ",";
	}
	outString = outString + std::to_string(playerToMove);
	std::cout << outString << std::endl;
}

void game::move(int slotNum) {
	int stonesPlayed = 0;
	int stoneCount = slotVec[slotNum];
	int opposingPlayer = playerToMove % 2 + 1; // Toggles 1 <-> 2
	std::cout << "Stone Count: " << stoneCount << std::endl;
	slotVec[slotNum] = 0;
	while (stonesPlayed < stoneCount) {
		--slotNum;
		if (slotNum == mancalaSlots[opposingPlayer])
			continue;
		if (slotNum < 0)
			slotNum = slotVec.size() - 1;
		slotVec[slotNum] += 1;
		++stonesPlayed;
	}
	if (slotNum != mancalaSlots[playerToMove])
		playerToMove = opposingPlayer;
}

std::vector<int> game::listMoves() {
	std::vector<int> movables;
	int homeSlot = mancalaSlots[playerToMove] + 1;
	while (homeSlot <= mancalaSlots[playerToMove] + SLOTS) {
		if (slotVec[homeSlot] > 0)
			movables.push_back(homeSlot);
		++homeSlot;
	}
	return movables;
}
