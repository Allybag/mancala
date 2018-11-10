#include "tcp_client.h"
#include "game.h"
#include "engine.cc"
#define PORT 18877

int main() {
    const char* host = "localhost";
    char recvBuff[512];
    std::string firstToMove;
    std::string sendStr;
    tcp_client tcpClient;
	game gameState;
	std::vector<int> moveList;

    //connect to host
    if (!tcpClient.conn(host, PORT)) {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }

    while (true) {
        if (!tcpClient.receive(sizeof(recvBuff), recvBuff))
			break;
		gameState.accept(recvBuff);

        if (gameState.playerToMove == 2) {
			sendStr = play(gameState);
			std::cout << sendStr << std::endl;
			gameState.print();
            if (!tcpClient.send_data(sendStr))
                break;
        }
    }
    return 0;
}
