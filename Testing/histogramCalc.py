from matplotlib import pyplot as plt
import numpy as np
import cv2
import scipy.io
from PIL import Image
from os.path import dirname, join as pjoin
from collections import defaultdict

cap = cv2.VideoCapture('DepthVideo.mp4')

q = 0

rangexmin = 50
rangexmax = 480
rangeymin = 100
rangeymax = 240

matrix = scipy.io.loadmat('depth_list.mat')

defaultData = [0] * 480

# 17th frame at 200 x is a good line

for y in range(0, 480):
	defaultData[y] = matrix['depth_list'][17][y][200]

# print(defaultData)

# print(len(defaultData))

defaultMatrix = [defaultData] * 640

# print(len(defaultMatrix), len(defaultMatrix[0]))

# print(len(matrix['depth_list'][q]), len(matrix['depth_list'][q][0]))

subMatrix = [0] * 640

for x in range(0, 640):
	subMatrix[x] = [0] * 480

# print(len(subMatrix), len(subMatrix[0]))

# print(len(defaultMatrix), len(defaultMatrix[0]))

while(cap.isOpened()):

	for y in range(rangeymin, rangeymax):
		for x in range(rangeymin, rangeymax):
			subMatrix[x][y] = int(matrix['depth_list'][q][y][x]) - int(defaultMatrix[x][y])

	# print(subMatrix[200][200], int(matrix['depth_list'][q][200][200]), int(defaultMatrix[200][200]))

	search_dist_low = 1.0
	search_dist_low_tmp = int(search_dist_low * 1000)
	search_dist_high = 5.5

	search_dist_low = int(search_dist_low * 1000)
	search_dist_high = int(search_dist_high * 1000)

	search_interval = int((search_dist_high - search_dist_low) / 5)

	z, width, height = matrix['depth_list'].shape

	ret, frame = cap.read()
	
	gausBlur = frame

	histr = cv2.calcHist([matrix['depth_list'][q]],[0],None,[6000],[0,6000])

	array = []

	# allx = 0
	# ally = 0
	# numx = 0
	# numy = 0

	# for x in range(width):
	# 	for y in range(height):
	# 		if gausBlur[y][x] > 105 and gausBlur[y][x] < 110 and x > 400 and x < 550 and y > 100 and y < 200:
	# 			array += [(x, y)]
	# 			allx += x
	# 			ally += y
	# 			numx += 1
	# 			numy += 1

	# if numx != 0 and numy != 0:
	# 	avgx = allx / numx
	# 	avgy = ally / numy

	# 	cv2.circle(gausBlur, (int(avgx), int(avgy)), 3, (240,0,0), 1, 8, 0)
				# cv2.circle(gausBlur, (x, y), 1, (240,0,0), 1, 8, 0)
				# print(array)


	# for x in range(100, 540):
	# 	for y in range(135, 240):

	xmin = 10000
	xmax = 0
	distmin = 10000

	xmin1 = 10000
	xmax1 = 0
	distmin1 = 10000

	xmin2 = 10000
	xmax2 = 0
	distmin2 = 10000

	xmin3 = 10000
	xmax3 = 0
	distmin3 = 10000

	xmin4 = 10000
	xmax4 = 0
	distmin4 = 10000

	for y in range(rangexmin, rangexmax):
		for x in range(rangeymin, rangeymax):

			search_dist_low = search_dist_low_tmp

			if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
				cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

				if matrix['depth_list'][q][x][y] < distmin:
					distmin = matrix['depth_list'][q][x][y]
				if y > xmax:
					xmax = y
				if y < xmin:
					xmin = y

			search_dist_low += search_interval

			if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
				cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

				if matrix['depth_list'][q][x][y] < distmin1:
					distmin1 = matrix['depth_list'][q][x][y]
				if y > xmax1:
					xmax1 = y
				if y < xmin1:
					xmin1 = y

			search_dist_low += search_interval

			if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
				cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

				if matrix['depth_list'][q][x][y] < distmin2:
					distmin2 = matrix['depth_list'][q][x][y]
				if y > xmax2:
					xmax2 = y
				if y < xmin2:
					xmin2 = y

			search_dist_low += search_interval

			if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
				cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

				if matrix['depth_list'][q][x][y] < distmin3:
					distmin3 = matrix['depth_list'][q][x][y]
				if y > xmax3:
					xmax3 = y
				if y < xmin3:
					xmin3 = y

			search_dist_low += search_interval

			if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
				cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

				if matrix['depth_list'][q][x][y] < distmin4:
					distmin4 = matrix['depth_list'][q][x][y]
				if y > xmax4:
					xmax4 = y
				if y < xmin4:
					xmin4 = y

	# cv2.circle(gausBlur, (100, 200), 1, (0,0,255), 3, 8, 0)
	# print(matrix['depth_list'][q][200][100])

	if xmin < 10000:
		cv2.rectangle(gausBlur,(xmin,150),(xmax,205),(0,0,255),3)

		array += [(xmin, xmax, distmin / 1000)]

	if xmin1 < 10000:
		cv2.rectangle(gausBlur,(xmin1,150),(xmax1,205),(255,0,0),3)

		array += [(xmin1, xmax1, distmin1 / 1000)]

	if xmin < 10000:
		cv2.rectangle(gausBlur,(xmin2,150),(xmax2,205),(0,255,0),3)

		array += [(xmin2, xmax2, distmin2 / 1000)]

	if xmin < 10000:
		cv2.rectangle(gausBlur,(xmin3,150),(xmax3,205),(255,0,255),3)

		array += [(xmin3, xmax3, distmin3 / 1000)]

	if xmin < 10000:
		cv2.rectangle(gausBlur,(xmin4,150),(xmax4,205),(0,255,255),3)

		array += [(xmin4, xmax4, distmin4 / 1000)]

	# xmin = 10000
	# xmax = 0
	# distmin = 10000

	# search_dist_low += search_interval
	# print(search_dist_low)
	# print('\n')

	# for y in range(rangexmin, rangexmax):
	# 	for x in range(rangeymin, rangeymax):
	# 		if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
	# 			cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

	# 			if matrix['depth_list'][q][x][y] < distmin:
	# 				distmin = matrix['depth_list'][q][x][y]
	# 			if y > xmax:
	# 				xmax = y
	# 			if y < xmin:
	# 				xmin = y

	# 			matrix['depth_list'][q][x][y] = 0

	# if xmin < 10000:
	# 	cv2.rectangle(gausBlur,(xmin,150),(xmax,205),(255,0,255),3)

	# 	array += [(xmin, xmax, distmin / 1000)]

	# xmin = 10000
	# xmax = 0
	# distmin = 10000

	# search_dist_low += search_interval
	# print(search_dist_low)
	# print('\n')
	
	# for y in range(rangexmin, rangexmax):
	# 	for x in range(rangeymin, rangeymax):
	# 		if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
	# 			cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

	# 			if matrix['depth_list'][q][x][y] < distmin:
	# 				distmin = matrix['depth_list'][q][x][y]
	# 			if y > xmax:
	# 				xmax = y
	# 			if y < xmin:
	# 				xmin = y

	# 		matrix['depth_list'][q][x][y] = 0

	# # if xmin < 10000:
	# # 	cv2.rectangle(gausBlur,(xmin,150),(xmax,205),(255,255,0),3)

	# # 	array += [(xmin, xmax, distmin / 1000)]

	# xmin = 10000
	# xmax = 0
	# distmin = 10000

	# search_dist_low += search_interval
	# print(search_dist_low)
	# print('\n')

	# for y in range(rangexmin, rangexmax):
	# 	for x in range(rangeymin, rangeymax):
	# 		if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
	# 			cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

	# 			if matrix['depth_list'][q][x][y] < distmin:
	# 				distmin = matrix['depth_list'][q][x][y]
	# 			if y > xmax:
	# 				xmax = y
	# 			if y < xmin:
	# 				xmin = y

	# 		matrix['depth_list'][q][x][y] = 0

	# if xmin < 10000:
	# 	cv2.rectangle(gausBlur,(xmin,150),(xmax,205),(255,0,0),3)

	# 	array += [(xmin, xmax, distmin / 1000)]

	# xmin = 10000
	# xmax = 0
	# distmin = 10000

	# search_dist_low += search_interval
	# print(search_dist_low)
	# print('\n')

	# for y in range(rangexmin, rangexmax):
	# 	for x in range(rangeymin, rangeymax):
	# 		if matrix['depth_list'][q][x][y] > search_dist_low and matrix['depth_list'][q][x][y] < search_dist_low + search_interval:
	# 			cv2.circle(gausBlur, (y, x), 1, (0,255,0), 1, 8, 0)

	# 			if matrix['depth_list'][q][x][y] < distmin:
	# 				distmin = matrix['depth_list'][q][x][y]
	# 			if y > xmax:
	# 				xmax = y
	# 			if y < xmin:
	# 				xmin = y

	# 		matrix['depth_list'][q][x][y] = 0

	# if xmin < 10000:
	# 	cv2.rectangle(gausBlur,(xmin,150),(xmax,205),(0,255,0),3)

	# 	array += [(xmin, xmax, distmin / 1000)]

	print(array)

	cv2.imshow('frame',gausBlur)

	plt.plot(histr[2:])

	plt.title('Histogram of Depth Data')
	plt.xlabel('Distance')
	plt.ylabel('Number of Pixels')

	plt.show()

	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

	q += 1

cap.release()
cv2.destroyAllWindows()