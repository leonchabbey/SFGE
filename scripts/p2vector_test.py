from SFGE import *
import sys
import random

class P2vectorTest(Component):

	def init(self):
		test = p2Vec2(1.0, 1.0)
		test.self.Show()
		print(test.x)
