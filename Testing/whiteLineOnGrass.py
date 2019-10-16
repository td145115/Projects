import numpy as np
import cv2
from timeit import default_timer as timer

cap = cv2.VideoCapture('Video3/CapVideo.mp4')

class LineDetection:
	def __init__(self):
		self.frame = np.zeros((640,480, 3), np.uint8)
		self.colorLow = 150
		self.colorHigh = 255

	def whiteLineOnGrass(self, frame):
		rangexmin = 0
		rangexmax = 640
		rangeymin = 150
		rangeymax = 340

		cutsize = 0

		minslope = .07

		rightlines = None
		leftlines = None
		horizontallines = None

		kernal = np.ones((2,2),np.uint8)

		grayscaled = cv2.cvtColor(frame[rangexmin:rangexmax][rangeymin:rangeymax], cv2.COLOR_BGR2GRAY)
		grayscaled = cv2.GaussianBlur(grayscaled, (5,5),0)

		_, th = cv2.threshold(grayscaled, self.colorLow, self.colorHigh,cv2.THRESH_BINARY)
		output = cv2.bitwise_and(frame[rangexmin:rangexmax][rangeymin:rangeymax], frame[rangexmin:rangexmax][rangeymin:rangeymax], mask = th)

		# cv2.imshow("output1", output)

		output = cv2.morphologyEx(output, cv2.MORPH_OPEN, kernal, iterations = 3)

		# cv2.imshow("output", output)

		mean = output.mean(axis =0).mean(axis = 0)


		if mean.mean() > 6.0:
			self.colorLow += 2
		elif mean.mean() < 0.5:
			self.colorLow -= 2

		output1 = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY)

		lines = cv2.HoughLinesP(output1, 1, np.pi/180, threshold = 100, minLineLength = 75, maxLineGap = 50)
		# print(lines[0][0][1])

		if lines is not None:
			# for x1, y1, x2, y2 in lines[0]:
			x1, y1, x2, y2 = lines[0][0][0], lines[0][0][1] + rangeymin, lines[0][0][2], lines[0][0][3] + rangeymin

			# lines[0][0][1] += rangeymin
			# lines[0][0][3] += rangeymin
			# print(abs(((y2-y1)/(x2-x1))))

			if (x1 > (rangexmin + int(cutsize/2)) or x1 < (rangexmax - int(cutsize/2))) and ((abs(((y2-y1)/(x2-x1))) > minslope)):
				if (y2-y1)/(x2-x1) > 0:
					#left side
					leftlines = [[x1, y1], [x2, y2]]

				elif (y2-y1)/(x2-x1) < 0:
					#right side
					rightlines = [[x1, y1], [x2, y2]]
			if (abs(((y2-y1)/(x2-x1))) < minslope):
				horizontallines = [[x1, y1], [x2, y2]]
		if rightlines is None:
			rightlines = []
		if leftlines is None:
			leftlines = []
		if horizontallines is None:
			horizontallines = []
		
		# print(rightlines, leftlines, horizontallines)

		return rightlines, leftlines, horizontallines




ld = LineDetection()

while(cap.isOpened()):
	start = timer()

	ret, frame = cap.read()

	rightlines, leftlines, horizontallines = ld.whiteLineOnGrass(frame)

	# print(rightlines)

	if rightlines != []:
		x1, y1, x2, y2 = rightlines[0][0], rightlines[0][1], rightlines[1][0], rightlines[1][1]
		# for x1, y1, x2, y2 in rightlines[0]:
		cv2.line(frame, (x1,y1), (x2,y2), (0,255,0), 5)

	if leftlines != []:
		x1, y1, x2, y2 = leftlines[0][0], leftlines[0][1], leftlines[1][0], leftlines[1][1]
		# for x1, y1, x2, y2 in leftlines[0]:
		cv2.line(frame, (x1,y1), (x2,y2), (255,0,0), 5)
	if horizontallines != []:
		x1, y1, x2, y2 = horizontallines[0][0], horizontallines[0][1], horizontallines[1][0], horizontallines[1][1]
		# for x1, y1, x2, y2 in leftlines[0]:
		cv2.line(frame, (x1,y1), (x2,y2), (0,0,255), 5)

	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

	cv2.imshow('frame',frame)

	end = timer()
	print(end - start)

cap.release()
cv2.destroyAllWindows()
