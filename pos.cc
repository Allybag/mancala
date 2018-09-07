#include "pos.h"

pos::pos(const char* recvBuff)
{
	int slotCount = 0;
	const char* recvChar = recvBuff;
	while (*recvChar)
	{
		if (*recvChar == ',')
		{
			position.push_back(slotCount);
			slotCount = 0;
		} else if (isdigit(*recvChar)) {
			slotCount *= 10;
			slotCount += (*recvChar - '0');
		} else if (*recvChar == 'T') {
			firstToMove = true;
			break;
		} else if (*recvChar == 'F') {
			firstToMove = false;
			break;
		}
		++recvChar;
	}
}
