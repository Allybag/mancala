#include "game.h"

std::string play(game gameState)
{
	std::string movesMade;
	auto initialPlayer = gameState.playerToMove;
	while (gameState.playerToMove == initialPlayer) {
		auto moveList = gameState.listMoves();
		unsigned long randomInt = rand() % moveList.size();
		auto randomMove = moveList[randomInt];
		gameState.move(randomMove);
		movesMade += std::to_string(randomMove);
		movesMade += ",";
	}
    return movesMade;
}
