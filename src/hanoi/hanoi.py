#!/usr/bin/env python


import sys


ANSIC = "\x1B["
RESET = ANSIC + "m"
RED = ANSIC + "31;40m"
GREEN = ANSIC + "32;40m"
YELLOW = ANSIC + "33;40m"

#sys.setrecursionlimit(15)

class TowerController(object):
	def __init__(self):
		self.__auxTower = None
		self.totalDiscs = -1
		self.__initTower = None
		self.__destinationTower = None


	def move1(self, source, dest, aux):
		"""
		How to move 1 item
		"""
		self.moveOperation(source, dest)
		
		

	def move2(self, source, dest, aux):
		"""
		How to move 2 items
		"""
		self.moveOperation(source, aux)
		self.moveOperation(source, dest)
		self.moveOperation(aux, dest)

	def move3(self, source, dest, aux):
		"""
		How to move 3 items
		"""
		self.moveOperation(source, dest)
		self.moveOperation(source, aux)
		self.moveOperation(dest, aux)
		self.moveOperation(source, dest)
		self.moveOperation(aux, source)
		self.moveOperation(aux, dest)
		self.moveOperation(source, dest)

	def moveN(self, x, source, dest, aux, debug = False):
		"""
		Defines single movements for n items
		"""
		if x < 1:
			return

		if x == 1:
			self.move1(source, dest, aux)
			self.printTowers(source, dest, aux)
			return
		if x == 2:
			self.move2(source, dest, aux)
			self.printTowers(source, dest, aux)
			return

		if x == 3:
			self.move3(source, dest, aux)
			self.printTowers(source, dest, aux)
			return
		else:
			self.moveN(x-1, source, aux, dest)
			self.moveN(1, source, dest, aux)
			self.moveN(x-1, aux, dest, source)


	def moveDisks(self, source=None, destination=None, tbuffer=None, debug = False):
		"""
		Determine whats needed to move an entire stack
		"""

		if source is None:
			source = self.__initTower

		if destination is None:
			destination = self.__destinationTower

		if tbuffer is None:
			tbuffer = self.__auxTower

		moves = source.determineMoves(destination.getTop())

		if moves < 1:
			return

		self.moveN(moves, source, destination, tbuffer, debug)
		
		if source.getCount() == 0 and destination.getCount() == self.totalDiscs:
			return

		self.moveDisks(tbuffer, destination, source, debug)

		
	def moveOperation(self, srcTower, destTower):
		"""
		Simple move operation
		"""
		toMoveValue = srcTower.getTop()

		if toMoveValue is None:
			return False

		if destTower.canReceive(toMoveValue):
			srcTower.popDisk()
			destTower.pushDisk(toMoveValue)
			return True
		return False


	def printTowers(self, src = None, aux = None, dest = None):
		"""
		Iterate over towers
		"""
		
		srcTag = "Src"
		auxTag = "Aux"
		destTag = "Dest"

		if self.__initTower == aux:
			srcTag = "Aux"
		if self.__initTower == dest:
			srcTag = "Dest"

		if self.__auxTower == src:
			auxTag = "Src"
		if self.__auxTower == dest:
			auxTag = "Dest"

		if self.__destinationTower == aux:
			destTag = "Aux"
		if self.__destinationTower == src:
			destTag = "Src"

		print "Src:  ", self.__initTower.getDiskRepr(), srcTag
		print "Aux:  ", self.__auxTower.getDiskRepr(), auxTag
		print "Dest: ", self.__destinationTower.getDiskRepr(), destTag
		print "*" * 20

	def setup(self, towercount, valueCount):
		"""
		Set tower up
		"""
		self.__initTower = Tower()
		self.__destinationTower = Tower()
		
		vCnt = range(valueCount)
		vCnt.reverse()
		self.totalDiscs = len(vCnt)
		for value in vCnt:
			self.__initTower.pushDisk(value)

		totalTowers = towercount - 2
		if totalTowers < 1:
			return

		self.__auxTower = Tower()



class Tower(object):
	def __init__(self):
		self.__disks = []

	def canReceive(self, value):
		if self.empty():
			return True

		if value > self.__disks[-1]:
			return False
		return True

	def pushDisk(self, value):
		self.__disks.append(value)

	def empty(self):
		return len(self.__disks) == 0

	def popDisk(self):
		return self.__disks.pop()

	def getTop(self):
		if len(self.__disks) > 0:
			return self.__disks[-1]
		return None

	def getDiskRepr(self):
		return str(self.__disks)

	def getCount(self):
		return len(self.__disks)

	def determineMoves(self, destTop):
		if destTop is None:
			return len(self.__disks)

		disks = list(self.__disks)
		disks.reverse()
		for item, disk in enumerate(disks):
			if disk > destTop:
				return item - 1
		return len(self.__disks)



if __name__ == "__main__":
	tc = TowerController()
	tc.setup(3, 9)
	tc.printTowers()
	tc.moveDisks()
