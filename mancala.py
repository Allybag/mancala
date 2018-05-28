import cfg
from core import Position

def main():
	piecesPerSlot = cfg.stones
	startingBoard = ([0] + [piecesPerSlot] * cfg.slots) * 2
	pos = Position(startingBoard, 0)

	move = None
	while True:
		print(pos)
		print(pos.listMoves())
		move = int(input())
		print(move)
		pos = pos.move(move)

if __name__ == '__main__':
	main()
