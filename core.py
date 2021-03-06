from collections import namedtuple
import cfg

class Position(namedtuple('Position', ['stoneList', 'playerToMove'])):
    """stoneList represents the state of the board
    a list of fourteen numbers representing stones in each slot
    stoneList[0] is Player 2's home slot, cfg.stones their last slot,
    (cfg.stones + 1) Player 1's home and (2 * cfg.stones + 1) their last.

    playerToMove is either 0 (first) or 1 (second)"""

    def __init__(self, stoneList, playerToMove):
        self.n = (cfg.slots + 1) # Useful number, distance between mancalas
        self.homeMancala = 0 if playerToMove else self.n
        self.oppMancala = self.n if playerToMove else 0
        self.totalSlots = 2 * self.n
        self.homeSlots = range(self.homeMancala + 1, self.homeMancala + self.n)
        self.oppSlots = range(self.oppMancala + 1, self.oppMancala + self.n)
        self.score = stoneList[self.n] - stoneList[0] # Score diff for Player 1

    def __repr__(self):
        """We represent the board as a string of two lines.
        Player 2's home slot on line 1 left, P1 on line 2 right"""
        repString = "("
        for slot in range(self.n): # Top row
            repString += "{} ".format(self.stoneList[slot])
        repString += " )\n"

        repString += "( "
        for slot in range((self.totalSlots - 1), cfg.slots, -1): # Bottom row
            repString += " {}".format(self.stoneList[slot])
        repString += ")"
        return repString

    def listMoves(self):
        """ Returns a list of valid slots to move """
        moveList = [slot for slot in self.homeSlots if self.stoneList[slot] > 0]
        if cfg.finalScoreAllPieces and not moveList:
            oppStoneCount = sum([self.stoneList[slot] for slot in self.oppSlots])
            self.score -= oppStoneCount # Final move will never change player
        return moveList

    def nextSlot(self, slot, startSlot):
        """ Returns the next slot in the cycle """
        candidateSlot = (slot - 1) % self.totalSlots
        startSlot = startSlot if cfg.skipOrigin else None

        while candidateSlot == self.oppMancala or candidateSlot == startSlot:
            candidateSlot -= 1
        return candidateSlot

    def capNever(self, slot):
        return self.stoneList

    def capOppLoner(self, slot):
        nextPos = self.stoneList[:]
        if self.stoneList[slot] == 2 and slot in self.oppSlots: # slot was 1 before move
            nextPos[slot] = 0
            nextPos[self.homeMancala] += 2
        return nextPos

    def capRowHomeEmpty(self, slot): # Ridiculously powerful, from play-mancala.com
        nextPos = self.stoneList[:]
        if self.stoneList[slot] == 1 and slot in self.homeSlots:
            oppSlot = self.totalSlots - slot
            cappedStoneCount = 1 + self.stoneList[oppSlot]
            nextPos[slot] = nextPos[oppSlot] = 0
            nextPos[self.homeMancala] += cappedStoneCount
        return nextPos

    cap_dict = {None: capNever, 'finalOnEnemySingletonCapSlot': capOppLoner,
                'finalOnHomeEmptyCapRow': capRowHomeEmpty}
    checkCapture = cap_dict[cfg.captureMethod]

    def resolve(self, slot):
        resolvedPosition = self.checkCapture(slot)
        nextPlayer = self.playerToMove if slot == self.homeMancala else not self.playerToMove

        return Position(resolvedPosition, nextPlayer)

    def move(self, slot):
        """Takes the current position, and a slot from which
        to start, and returns the resulting position if valid"""
        if slot not in self.listMoves():
            print("Please enter a valid slot to move")
            return self

        startSlot = slot
        nextPos = self.stoneList[:]
        nextPos[slot] = 0 # Clear the picked up slot

        for i in range(self.stoneList[slot]):
            slot = self.nextSlot(slot, startSlot)
            nextPos[slot] += 1

        return Position(nextPos, self.playerToMove).resolve(slot)
