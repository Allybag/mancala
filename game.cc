#include "game.h"
#include <algorithm>
#define SLOTS 6


game::game(const char* recvBuff)
{
	int slotCount = 0;
	int totalSlots = 0;
	Slot* head = nullptr;
	const char* recvChar = recvBuff;
	while (*recvChar)
	{
		if (*recvChar == ',')
		{
			Slot* s = new Slot();
			s->count = slotCount;
			s->next = head;
			head = s;
			slotCount = 0;
			if (totalSlots == 0)
				firstMancala = s;
			if (totalSlots == (SLOTS + 1))
				secondMancala = s;
			++totalSlots;
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

}

