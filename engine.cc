#include<iostream>    //std::cout
#include<string>  //std::string
#include<vector> //std::vector
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include<cstdlib> //rand()
#include<cctype> //isdigit()
#define PORT 18877

class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    tcp_client();
    bool conn(const char*, int);
    bool send_data(std::string&);
    bool receive(size_t, char*);
};

tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}

bool tcp_client::conn(const char* address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }
    }

    //setup address structure
    if(inet_addr(address) == -1)
    {
        struct hostent *host_entry;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ((host_entry = gethostbyname(address)) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            std::cout << "Failed to resolve hostname\n";
            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) host_entry->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            server.sin_addr = *addr_list[i];
            break;
        }
    }
    else
    {
        //plain ip address
        server.sin_addr.s_addr = inet_addr(address);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return false;
    }

    std::cout << "Connected\n";
    return true;
}

bool tcp_client::send_data(std::string& data)
{
    if (send(sock, data.c_str(), data.length(), 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    return true;
}

bool tcp_client::receive(size_t recvBuffSize, char* recvBuff)
{
    if (recv(sock, recvBuff, recvBuffSize, 0) <= 0)
    {
		recvBuff[0] = '\0';
        std::cout << "Socket receive closed." << std::endl;
		return false;
    }
	return true;
}

struct pos
{
private:
	std::vector<int> position;

public:
	pos(const char*);
	bool firstToMove;
};

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
