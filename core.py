from collections import namedtuple

class Position(namedtuple('Position', ['boardList', 'playerToMove'])):
	# boardList represents the state of the board
	# a list of fourteen numbers representing stones in each slot
	# boardList[0] is Player 2's home slot, 6 their last slot,
	# 7 Player 1's home and 13 is Player 2's last slot.

	def __repr__(self):
		"""We represent the board as a string of two lines.
		Player 2's home slot on line 1 left, P1 on line 2 right"""
		repString = "("
		for slot in range(7):
			repString += "{} ".format(self.boardList[slot])
		repString += " )\n"

		repString += "( "
		for slot in range(13, 6, -1):
			repString += " {}".format(self.boardList[slot])
		repString += ")"

		return repString

piecesPerSlot = 4
startingBoard = ([0] + [piecesPerSlot] * 6) * 2
startPos = Position(boardList = startingBoard, playerToMove = 1)
