#include "tcp_client.h"

tcp_client::tcp_client() {
    sock = -1;
    port = 0;
    address = "";
}

bool tcp_client::conn(const char* connAddress , int connPort) {
    //create socket if it is not already created
    if(sock == -1) {
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1) {
            perror("Could not create socket");
        }
    }

    //setup address structure
    if(inet_addr(connAddress) == -1) {
        struct hostent *host_entry;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ((host_entry = gethostbyname(connAddress)) == NULL) {
            //gethostbyname failed
            herror("gethostbyname");
            std::cout << "Failed to resolve hostname\n";
            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) host_entry->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++) {
            server.sin_addr = *addr_list[i];
            break;
        }
    } else {
        //plain ip address
        server.sin_addr.s_addr = inet_addr(connAddress);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(connPort);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        return false;
    }

    std::cout << "Connected\n";
    return true;
}

bool tcp_client::send_data(std::string& data) {
    if (send(sock, data.c_str(), data.length(), 0) < 0) {
        perror("Send failed : ");
        return false;
    }
    return true;
}

bool tcp_client::receive(size_t recvBuffSize, char* recvBuff) {
    if (recv(sock, recvBuff, recvBuffSize, 0) <= 0) {
		recvBuff[0] = '\0';
        std::cout << "Socket receive closed." << std::endl;
		return false;
    }
	return true;
}
