import random
import cfg
from core import Position


def play(pos):
    colour = 1 if cfg.enginePlayer == 0 else -1
    (highScore, move) = negaMax(pos, cfg.depth, colour)

    if not move: # We were given depth 0
        move = random.choice(pos.listMoves())
        print("Playing {} at random!".format(move))
    pos = pos.move(move)
    print("Playing move {} with score {}".format(move, highScore))
    return (pos, move)

def negaMax(pos, depth, colour):
    """Recursively find the best move via a negamax search"""
    candidateMoves = pos.listMoves()
    bestMove = None
    if depth == 0 or not candidateMoves:
        return (pos.score * colour, bestMove)

    highScore = -(cfg.slots * cfg.stones)

    for move in candidateMoves:
        candidatePos = pos.move(move)
        if candidatePos.playerToMove == pos.playerToMove:
            #print("{}: {} going deeper!".format(pos, move))
            # Search moves where we keep out turn deeper by leaving depth unchanged
            score = negaMax(candidatePos, depth, colour)[0]
        else:
            score = -negaMax(candidatePos, depth - 1, -colour)[0]
        #highScore = max(score, highScore)
        if score > highScore:
            highScore, bestMove = score, move

    return (highScore, bestMove)
