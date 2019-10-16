# By: Trenton Davis, Jared Chudzinski, Mehdi Rezaie

import pandas as pd
import numpy as np
import operator

# This is the tree data structure
class Tree(object):
	def __init__(self):
		self.left = None
		self.right = None
		self.data = None

# This is the Decision Tree class which holds all of the functions that are used in the making of the tree.
class DecisionTree(object):
	# We do not need to initialize anything, so we just pass through this.
	def __init__(self):
		pass

	# This function is our recursive function that calls the other required functions to create the tree, it is more or less the main
	# function of the code. bestmotif takes a list of sequences that are used to calculate phi.
	def bestmotif(self, seqindices):
		# Since we only need certain sequences from the data, we take only those that we need and save them into another list called mymotifs.
		global motifs
		mymotifs = motifs[seqindices, :]
		myclasses = classes[seqindices]

		# Root is the absolute root of the tree, we use this to store the data.
		global root

		# This is the call that breaks out of the recursion.
		if np.all(myclasses == 1) or np.all(myclasses == -1):
			return root

		# Placeholder is a list that we use to hold all of the phis of the motifs that we calculate.
		placeholder = []

		# This for loop stores all of the phi values for each motif, so that we can get the max one and use it in the next iteration.
		for motif in mymotifs.T:
			phi = self.phiCalc(*self.buildTree(myclasses,motif))
			placeholder.append(phi)

		# We are finding the index of the max phi value because it becomes the best motif for that branch of the tree.
		maxindex = np.argmax(placeholder)
		print("{:s} {:70s} {:10s} {:5.2f}".format("motif: ", motifNames[maxindex], " has a phi of ",np.max(placeholder)))
		awesomemotif = mymotifs[:,maxindex]
		root = self.positiveMotif(myclasses, awesomemotif, maxindex)

		global numberofmotifs
		numberofmotifs+=1

		# We are setting all of the data to 0 in the original data set for the particular motif that we used for this iteration so that it is not
		# always the motif that comes up.
		motifs[:,maxindex] = 0
		
		# Here is the recursive call for the left child of the root.
		self.bestmotif(root.left.data[0])
		# Here is the recursive call for the right child of the root.
		self.bestmotif(root.right.data[0])

	# This is the function to calculate the phi value. This was pulled off of the slides. It takes the elements that are returned from the
	# buildTree function.
	def phiCalc(self, classOneLeft, classTwoLeft, classOneRight, classTwoRight):
		# These variables are created for readability of the code, so it more resembles the function from the slides.
		totalLeft = classOneLeft + classTwoLeft
		totalRight = classOneRight + classTwoRight
		totalAll = totalLeft + totalRight

		if totalLeft == 0:
			return 0
		if totalRight == 0:
			return 0

		pLeft = totalLeft / totalAll
		pRight = totalRight / totalAll

		# This is the actual calculation of phi
		phi  = 2*pLeft*pRight*(abs(
								(classOneLeft/totalLeft) - (classOneRight/totalRight)) +
							 abs(
								(classTwoLeft/totalLeft) - (classTwoRight/totalRight)))

		# This function returns the particular phi of the chosen motif.
		return phi

	# buildTree is used to determine the placement of each element. Right now, we only care about the number of elements in each side of the tree
	# and the classes that they belong to, so we calculate these numbers instead of the actual motif itself. This takes a particular motif and 
	# returns the desired information that will be used in phiCalc
	def buildTree(self, classification, motif):
		# classOneLeft is the number of elements that have a class of 1 and are covered by this motif.
		# classTwoLeft is the number of elements that have a class of -1 and are covered by this motif.
		# classOneRight is the number of elements that have a class of 1 and are not covered by this motif.
		# classTwoRight is the number of elements that have a class of -1 and are not covered by this motif.
		classOneLeft = ((motif == 1) & (classification == 1)).sum()
		classTwoLeft = ((motif == 1) & (classification == -1)).sum()
		classOneRight = ((motif == 0) & (classification == 1)).sum()
		classTwoRight = ((motif == 0) & (classification == -1)).sum()

		return classOneLeft, classTwoLeft, classOneRight, classTwoRight

	# positiveMotif takes the index of the motif with the maximum phi value from the last iteration. It then splits the sequences into leaves
	# that help to create the tree. 
	def positiveMotif(self, classification, motif, maxIndex):
		# root.data for the first iteration is the index of the motif that has the maximum phi at the beginning. Then it splits the sequences into 
		# left and right leaves similar to how we specified in the buildTree function.
		root = Tree()
		root.data = maxIndex
		root.left = Tree()
		root.right = Tree()
		positive = motif == 1
		indexLeft = np.argwhere(positive).flatten()
		indexRight = np.argwhere(~positive).flatten()
		root.left.data = [indexLeft, classification[indexLeft]]
		root.right.data = [indexRight, classification[indexRight]]

		# returning the root helps to make the recursion possible.
		return root


# Reading in the data
data = pd.read_csv("ETS.training.csv")

# copying the last column into a list. This list holds the classes, and is a global variable that does not change, but is referenced throughout
classes = data.iloc[:,-1].values

# copying all of the data to a list that does change throughout the runtime of the program.
motifs = data.iloc[:, 1:-1].values

# declaring a new decision tree.
dt = DecisionTree()

# getting the names of the motifs for easier access later.
motifNames = data.columns[1:-1]

numberofmotifs = 0

# Entering the first iteration of the program, this is all of the data, and starts the recursion.
dt.bestmotif(np.arange(motifs.shape[0]))

print("There are ", numberofmotifs, " motifs")
