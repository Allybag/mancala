#include "game.h"
#include <algorithm>
#define SLOTS 6


game::game(const char* recvBuff)
{
	int slotCount = 0;
	slot* head = nullptr;
	const char* recvChar = recvBuff;
	while (*recvChar)
	{
		if (*recvChar == ',')
		{
			slot* s = new slot();
			s->count = slotCount;
			s->next = head;
			s->prev = nullptr;
			if (head) // If we're not the first element`
				head->prev = s;
			head = s;
			slotVec.push_back(*s);
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
	firstMancala  = &(slotVec[0]);
	secondMancala = &(slotVec[(SLOTS + 1)]);
	// Make the linked list cyclical
	slotVec.front().next = &(slotVec.back());
	slotVec.back().prev = &(slotVec.front());

}

void game::print() {
	std::string outString;
	for (auto gameSlot: slotVec) {
		outString = outString + std::to_string(gameSlot.count) + ",";
	}
	outString = outString + std::to_string(playerToMove);
	std::cout << outString << std::endl;
}

void game::move(int slotNum) {
	int stonesPlayed = 0;
	slot* dropSlot = slotVec[slotNum].next;
	while (stonesPlayed < slotNum) {
		dropSlot->count += 1;
		dropSlot = dropSlot->next;
		++stonesPlayed;
	}
}
