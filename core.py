from collections import namedtuple
import cfg

class Position(namedtuple('Position', ['boardList', 'playerToMove'])):
	"""boardList represents the state of the board
	a list of fourteen numbers representing stones in each slot
	boardList[0] is Player 2's home slot, 6 their last slot,
	7 Player 1's home and 13 is Player 2's last slot.

	playerToMove is either 0 (first) or 1 (second)"""

	def __repr__(self):
		"""We represent the board as a string of two lines.
		Player 2's home slot on line 1 left, P1 on line 2 right"""
		repString = "("
		for slot in range(cfg.slots + 1): # Top row
			repString += "{} ".format(self.boardList[slot])
		repString += " )\n"

		repString += "( "
		for slot in range((totalSlots - 1), cfg.slots, -1): # Bottom row
			repString += " {}".format(self.boardList[slot])
		repString += ")"

		return repString

	def generateMoves(self):
		""" Returns a list of valid slots to move """
		moveList = []

		startSlot = 1 if self.playerToMove else (cfg.slots + 2)

		for slot in range(startSlot, startSlot + cfg.slots):
			if self.boardList[slot] > 0:
				moveList.append(slot)

		return moveList

	def nextSlot(self, slot, startSlot):
		""" Returns the next slot in the cycle """
		candidateSlot = (slot - 1) % totalSlots

		skipSlot = (cfg.slots + 1) if self.playerToMove else 0
		startSlot = startSlot if cfg.skipOrigin else None

		while candidateSlot == skipSlot or candidateSlot == startSlot:
			candidateSlot -= 1

		return candidateSlot

	def move(self, slot):
		"""Takes the current position, and a slot from which
		to start, and returns the resulting position if valid"""
		if slot not in self.generateMoves():
			print("Please enter a valid slot to move")
			return self

		startSlot = slot
		newBoardList = self.boardList[:]
		piecesToMove = self.boardList[slot]
		newBoardList[slot] = 0 # Clear the picked up slot
		homeSlot = 0 if self.playerToMove else 7

		for i in range(piecesToMove):
			slot = self.nextSlot(slot, startSlot)
			newBoardList[slot] += 1

		nextPlayer = self.playerToMove if slot == homeSlot else not self.playerToMove

		return Position(newBoardList, nextPlayer)


piecesPerSlot = cfg.stones
totalSlots = (2 * cfg.slots + 2)
startingBoard = ([0] + [piecesPerSlot] * cfg.slots) * 2
startPos = Position(boardList = startingBoard, playerToMove = 0)
