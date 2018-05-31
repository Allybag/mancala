import cfg
import engine
from core import Position

def main():
    piecesPerSlot = cfg.stones
    startingBoard = ([0] + [piecesPerSlot] * cfg.slots) * 2
    pos = Position(startingBoard, 0)
    notation = []

    move = None
    while True:
        print(pos)
        print("Current game:{}".format(' '.join([str(move) for move in notation])))

        if not pos.listMoves():
            winner = "first" if pos.score > 0 else "second" if pos.score < 0 else None
            print("Game Over!")
            if winner:
                print("Win for {} player!".format(winner))
            break
        if cfg.enginePlayer == pos.playerToMove:
            print("Playing Engine Move")
            pos, move = engine.play(pos)
            notation.append(move)
            continue
        #else: # For engine self play
            #cfg.enginePlayer = pos.playerToMove
            #continue

        move = int(input())
        if move in pos.listMoves():
            # Trying an invalid move is safe, but we don't want to record it
            notation.append(move)
        pos = pos.move(move)

if __name__ == '__main__':
    main()
