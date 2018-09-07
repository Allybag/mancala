#ifndef TCP_H
#define TCP_H
#include<iostream>    //std::cout
#include<string>  //std::string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent

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
#endif
