#include "tcp_client.h"
#include "game.h"
#define PORT 18877

int main() {
    const char* host = "localhost";
    char recvBuff[256];
    std::string firstToMove;
    std::string randomMove;
    tcp_client client;

    //connect to host
    if (!client.conn(host, PORT)) {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }

    while (true) {
        if (!client.receive(sizeof(recvBuff), recvBuff))
			break;
		game gameState(recvBuff);
        std::cout << gameState.getScore() << std::endl;
		std::cout << recvBuff << std::endl;
        gameState.print();


        if (gameState.playerToMove == 2) {
            randomMove = std::to_string((rand() % 6) + 8);
            if (!client.send_data(randomMove))
                break;
        }
    }
    return 0;
}
