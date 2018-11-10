#include "tcp_client.h"
#include "game.h"
#define PORT 18877

int main() {
    const char* host = "localhost";
    char recvBuff[256];
    std::string firstToMove;
    int randomMove;
    std::string sendStr;
    tcp_client client;
	game gameState;
	std::vector<int> moveList;

    //connect to host
    if (!client.conn(host, PORT)) {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }

    while (true) {
        if (!client.receive(sizeof(recvBuff), recvBuff))
			break;
		gameState.accept(recvBuff);

        if (gameState.playerToMove == 2) {
			moveList = gameState.listMoves();
            unsigned long randomInt = rand() % moveList.size();
			randomMove = moveList[randomInt];
			std::cout << "Score before: " << gameState.score() << std::endl;
			gameState.move(randomMove);
			std::cout << "Score after: " << gameState.score() << std::endl;
			gameState.print();
            sendStr = std::to_string(randomMove);
            if (!client.send_data(sendStr))
                break;
        }
    }
    return 0;
}
