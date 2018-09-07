#include "tcp_client.h"
#include "pos.h"
#define PORT 18877

int main(int argc , char *argv[])
{
    const char* host = "localhost";
    char recvBuff[256];
    std::string firstToMove;
    std::string randomMove;
    tcp_client client;

    //connect to host
    if (!client.conn(host, PORT))
    {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }

    while (true)
    {
        if (!client.receive(sizeof(recvBuff), recvBuff))
			break;
        std::cout << recvBuff << std::endl;
		pos recvPos(recvBuff);

        if (!recvPos.firstToMove)
        {
            randomMove = std::to_string((rand() % 6) + 8);
            if (!client.send_data(randomMove))
                break;
        }
    }

    return 0;
}
