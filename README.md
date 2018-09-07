# mancala
Command Line game of Mancala

Can play over a socket with a remote opponent, on port 18877, by setting remoteEngine = true in cfg.py
mancala.py expects to receive a single int representing a move beginning from a legal board position, and then replies with a null terminated ASCII comma delimited string, detailing the number of stones in each slot, followed by whether or not it is the first player's turn (True or False)

engine.cc can be compiled into an opponent to play against, by compiling with "g++ engine.cc" and running the resulting binary with no arguments
