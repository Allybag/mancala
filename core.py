from collections import namedtuple
import cfg

class Position(namedtuple('Position', ['stoneList', 'playerToMove'])):
	"""stoneList represents the state of the board
	a list of fourteen numbers representing stones in each slot
	stoneList[0] is Player 2's home slot, cfg.stones their last slot,
	(cfg.stones + 1) Player 1's home and (2 * cfg.stones + 1) their last.

	playerToMove is either 0 (first) or 1 (second)"""

	def __init__(self, stoneList, playerToMove):
		self.homeSlot = 0 if playerToMove else (cfg.slots + 1)
		self.skipSlot = (cfg.slots + 1) if playerToMove else 0
		self.totalSlots = (2 * cfg.slots + 2)

	def __repr__(self):
		"""We represent the board as a string of two lines.
		Player 2's home slot on line 1 left, P1 on line 2 right"""
		repString = "("
		for slot in range(cfg.slots + 1): # Top row
			repString += "{} ".format(self.stoneList[slot])
		repString += " )\n"

		repString += "( "
		for slot in range((self.totalSlots - 1), cfg.slots, -1): # Bottom row
			repString += " {}".format(self.stoneList[slot])
		repString += ")"
		return repString

	def endGame(self):
		firstPlayerScore  = self.stoneList[cfg.slots + 1]
		secondPlayerScore = self.stoneList[0]
		if firstPlayerScore > secondPlayerScore:
			print("Player One Wins!")
		elif secondPlayerScore > firstPlayerScore:
			print("Player Two Wins!")
		else:
			print("It's a draw!")

	def listMoves(self):
		""" Returns a list of valid slots to move """
		moveList = []
		startSlot = 1 if self.playerToMove else (cfg.slots + 2)

		for slot in range(startSlot, startSlot + cfg.slots):
			if self.stoneList[slot] > 0:
				moveList.append(slot)
		if not moveList:
			self.endGame()

		return moveList

	def nextSlot(self, slot, startSlot):
		""" Returns the next slot in the cycle """
		candidateSlot = (slot - 1) % self.totalSlots
		startSlot = startSlot if cfg.skipOrigin else None

		while candidateSlot == self.skipSlot or candidateSlot == startSlot:
			candidateSlot -= 1
		return candidateSlot

	def capNever(self, slot):
		return self.stoneList

	def capLoner(self, slot):
		nextPos = self.stoneList[:]
		if self.stoneList[slot] == 2: # Must have been one before
			nextPos[slot] = 0
			nextPos[self.homeSlot] += 2
		return nextPos

	cap_dict = {None: capNever, 'finalOnSingleton': capLoner}
	checkCapture = cap_dict[cfg.captureMethod]

	def resolve(self, slot):
		resolvedPosition = self.checkCapture(slot)
		nextPlayer = self.playerToMove if slot == self.homeSlot else not self.playerToMove

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
