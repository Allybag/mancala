import cfg
from core import Position

def play(pos):
    moveScores = {}
    for move in pos.listMoves():
        moveScores[move] = negaMax(pos.move(move), cfg.depth, -100, -100)

    print(moveScores)
    move = min(moveScores.keys(), key=(lambda k: moveScores[k]))
    pos = pos.move(move)
    return pos

def negaMax(pos, depth, alpha, beta):
    """Recursively find the best move via a negamax search"""
    candidateMoves = pos.listMoves()
    if depth == 0 or not candidateMoves:
        return pos.score

    highScore = -100

    for move in candidateMoves:
        score = -negaMax(pos.move(move), depth - 1, -beta, -alpha)
        highScore = max(score, highScore)
        alpha = max(alpha, highScore)
        if alpha >= beta:
            break

    return highScore
