import random
import time
import cfg
from core import Position

def play(pos):
	candidates = pos.listMoves()
	move = random.choice(candidates)
	pos = pos.move(move)
	time.sleep(2)
	return pos
