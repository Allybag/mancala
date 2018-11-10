engine.out: main.cc game.cc tcp_client.cc game.h tcp_client.h engine.cc
	g++ -Wall -Werror -Wextra -Wunreachable-code -Wuninitialized -std=c++11 -o engine.out main.cc game.cc tcp_client.cc
