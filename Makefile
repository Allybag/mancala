engine.out: main.cc pos.cc tcp_client.cc pos.h tcp_client.h
	g++ -o engine.out main.cc pos.cc tcp_client.cc
