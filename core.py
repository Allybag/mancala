from collections import namedtuple

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
		for slot in range(7): # Top row
			repString += "{} ".format(self.boardList[slot])
		repString += " )\n"

		repString += "( "
		for slot in range(13, 6, -1): # Bottom row
			repString += " {}".format(self.boardList[slot])
		repString += ")"

		return repString

	def generateMoves(self):
		""" Returns a list of valid slots to move """
		moveList = []

		startSlot = 1 if self.playerToMove else 8

		for slot in range(startSlot, startSlot + 6):
			if self.boardList[slot] > 0:
				moveList.append(slot)

		return moveList

	def nextSlot(self, slot):
		""" Returns the next slot in the cycle """
		candidateSlot = (slot - 1) % 14

		skipSlot = 7 if self.playerToMove else 0

		if candidateSlot == skipSlot:
			candidateSlot -= 1

		return candidateSlot

	def move(self, slot):
		"""Takes the current position, and a slot from which
		to start, and returns the resulting position if valid"""
		if slot not in self.generateMoves():
			print("Please enter a valid slot to move")
			return self

		newBoardList = self.boardList[:]
		piecesToMove = self.boardList[slot]
		newBoardList[slot] = 0 # Clear the picked up slot
		homeSlot = 0 if self.playerToMove else 7

		for i in range(piecesToMove):
			slot = self.nextSlot(slot)
			newBoardList[slot] += 1

		if slot == homeSlot:
			nextPlayer = self.playerToMove
		else:
			nextPlayer = not self.playerToMove

		return Position(newBoardList, nextPlayer)


piecesPerSlot = 4
startingBoard = ([0] + [piecesPerSlot] * 6) * 2
startPos = Position(boardList = startingBoard, playerToMove = 0)
