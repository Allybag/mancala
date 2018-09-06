#include<iostream>    //std::cout
#include<string>  //std::string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include<cstdlib> //rand

std::string tail(std::string const& source, size_t const length) {
  if (length >= source.size()) { return source; }
  return source.substr(source.size() - length);
}

class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    tcp_client();
    bool conn(char*, int);
    bool send_data(std::string&);
    void receive(size_t, char*);
};

tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}

bool tcp_client::conn(char* address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        std::cout << "Socket created" << std::endl;
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
            std::cout << address << " resolved to " << inet_ntoa(*addr_list[i]) << std::endl;
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

    //Connect to remote server
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

void tcp_client::receive(size_t recvBuffSize, char* recvBuff)
{
    if (recv(sock, recvBuff, recvBuffSize, 0) < 0)
    {
	recvBuff[0] = '\0';
        std::cout << "recv failed" << std::endl;
    }
}

int main(int argc , char *argv[])
{
    char host[] = "localhost";
    char recvBuff[1024];
    std::string firstToMove;
    std::string randomMove;
    tcp_client client;

    //connect to host
    if (!client.conn(host, 18283))
    {
        std::cout << "Could not connect" << std::endl;
        return 1;
    }

    while (true)
    {
        //receive and echo reply
        client.receive(sizeof(recvBuff), recvBuff);
        std::cout << recvBuff;
        firstToMove = tail(recvBuff, 6);

        if (firstToMove == "False\n")
        {
            randomMove = std::to_string((rand() % 6) + 8);
            if (!client.send_data(randomMove))
                break;
        }
    }

    return 0;
}
