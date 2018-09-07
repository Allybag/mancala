import cfg
import engine
from core import Position
import sockBag

def main():
    piecesPerSlot = cfg.stones
    startingBoard = ([0] + [piecesPerSlot] * cfg.slots) * 2
    pos = Position(startingBoard, True)
    notation = []
    if cfg.remoteEngine:
        ceeSock = sockBag.makeSock()

    move = None
    while True:
        print(pos)
        print("Current game:{}".format(' '.join([str(move) for move in notation])))

        if cfg.remoteEngine:
            ceeSock.send(pos.machineRep())

        if not pos.listMoves():
            winner = "first" if pos.score < 0 else "second" if pos.score > 0 else None
            print("Game Over!")
            if winner:
                print("Win for {} player!".format(winner))
            break

        if cfg.engineIsFirst is not None:
            if cfg.engineIsFirst == pos.firstToMove:
                print("Playing Engine Move")
                if cfg.remoteEngine:
                    move = int(ceeSock.recv(256))
                    pos = pos.move(move)
                else:
                    pos, move = engine.play(pos)
                notation.append(move)
                continue

        move = int(input())

        if move in pos.listMoves():
            # Trying an invalid move is safe, but we don't want to record it
            notation.append(move)
        pos = pos.move(move)


if __name__ == '__main__':
    main()
