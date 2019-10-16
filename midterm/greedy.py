# Trenton Davis, Jared Chudzinski, Mehdi Rezaie

# This version gets the least amount of motifs that accounts for all sequences, not just all but the last 5 percent

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('ETS.Training.csv', index_col = 0)

stack = []

df = df.iloc[:df.shape[0] - 1,:df.shape[1] - 1]

columnNames = df.columns

helper = df.values

help1 = 0

# This function is the recursion method to the problem
def recursionToMax(helper):
	totals = helper.sum(axis = 0)
	biggest = np.max(totals)

	global help1
	help1 += biggest

	biggestIndex = np.where(totals == biggest)[0][0]

	if help1 / (helper.shape[0]) > .05 and biggest >= 100:
		for i in range(0, helper.shape[0]):
			if helper[i][biggestIndex] == 1:
				helper[i][:] = 0
		stack.append(biggestIndex)
		print(columnNames[biggestIndex], " accounts for ", biggest, " sequences")
		recursionToMax(helper)

recursionToMax(helper)

print(len(stack), " motifs cover ", int((help1/len(helper[0]))), "% of the sequences")