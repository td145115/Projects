# Trenton Davis, Jared Chudzinski, Mehdi Rezaie

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('AP1.csv', index_col = 0)

stack = []

# The range of values in the first one is 0:10000 which is the number of rows and the second one is 0:244 which is the number of columns

df = df.iloc[:df.shape[0] - 1,:df.shape[1] - 1]

columnNames = df.columns

helper = df.values

# This function is the recursion method to the problem
def recursionToMax(helper):
	totals = helper.sum(axis = 0)
	biggest = np.max(totals)
	biggestIndex = np.where(totals == biggest)[0][0]

	if biggest / (helper.shape[0]) > .05:
		for i in range(0, helper.shape[0]):
			if helper[i][biggestIndex] == 1:
				helper[i][:] = 0
		stack.append(biggestIndex)
		print(columnNames[biggestIndex], " accounts for ", biggest, " sequences")
		recursionToMax(helper)

recursionToMax(helper)

print(len(stack), " motifs")