engine.out: main.cc game.cc tcp_client.cc game.h tcp_client.h
	g++ -Wall -std=c++11 -o engine.out main.cc game.cc tcp_client.cc
