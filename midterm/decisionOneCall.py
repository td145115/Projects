import pandas as pd
import numpy as np
import operator

class Tree(object):
    def __init__(self):
        self.left = None
        self.right = None
        self.data = None


class DecisionTree(object):
	def __init__(self):
		pass

	def bestmotif(self, seqindices):
		global motifs
		mymotifs = motifs[seqindices, :]
		myclasses = classes[seqindices]

		global root

		if np.all(myclasses == 1) or np.all(myclasses == -1):
			return root

		placeholder = []

		for motif in mymotifs.T:
			phi = self.phiCalc(*self.buildTree(myclasses,motif))
			placeholder.append(phi)

		maxindex = np.argmax(placeholder)
		print(motifNames[maxindex], np.max(placeholder))
		awesomemotif = mymotifs[:,maxindex]
		root = self.positiveMotif(myclasses, awesomemotif, maxindex)

		motifs[:,maxindex] = 0

		self.bestmotif(root.left.data[0])
		self.bestmotif(root.right.data[0])

	def phiCalc(self, classOneLeft, classTwoLeft, classOneRight, classTwoRight):
		totalLeft = classOneLeft + classTwoLeft
		totalRight = classOneRight + classTwoRight
		totalAll = totalLeft + totalRight

		if totalLeft == 0:
			return 0
		if totalRight == 0:
			return 0

		pLeft = totalLeft / totalAll
		pRight = totalRight / totalAll
		phi  = 2*pLeft*pRight*(abs(
								(classOneLeft/totalLeft) - (classOneRight/totalRight)) +
							 abs(
								(classTwoLeft/totalLeft) - (classTwoRight/totalRight)))
		return phi

	def buildTree(self, classification, motif):
		classOneLeft = ((motif == 1) & (classification == 1)).sum()
		classTwoLeft = ((motif == 1) & (classification == -1)).sum()
		classOneRight = ((motif == 0) & (classification == 1)).sum()
		classTwoRight = ((motif == 0) & (classification == -1)).sum()
		return classOneLeft, classTwoLeft, classOneRight, classTwoRight

	def positiveMotif(self, classification, motif, maxIndex):
		root = Tree()
		root.data = maxIndex
		root.left = Tree()
		root.right = Tree()
		positive = motif == 1
		indexLeft = np.argwhere(positive).flatten()
		indexRight = np.argwhere(~positive).flatten()
		root.left.data = [indexLeft, classification[indexLeft]]
		root.right.data = [indexRight, classification[indexRight]]

		return root


data = pd.read_csv("ETS.training.csv")

classes = data.iloc[:,-1].values
motifs = data.iloc[:, 1:-1].values

dt = DecisionTree()

motifNames = data.columns[1:-1]

dt.bestmotif(np.arange(motifs.shape[0]))

# placeHolder = []
# for i, motif in enumerate(motifs.T):
# 	classOneLeft, classTwoLeft, classOneRight, classTwoRight = dt.buildTree(classes, motif)
# 	phi = dt.phiCalc(classOneLeft, classTwoLeft, classOneRight, classTwoRight)
# 	placeHolder.append(phi)

# firstIter = max(placeHolder)
# index = np.argmax(placeHolder)
# print(motifNames[index], firstIter)
# root = dt.positiveMotif(classes, motifs[:,index], index)

# motifs[:,index] = 0

# dt.bestmotif(root.left.data[0])
# dt.bestmotif(root.right.data[0])

# print(root.left.data, root.left.right.data)







