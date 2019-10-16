from matplotlib import pyplot as plt
import numpy as np
import cv2
import scipy.io
from PIL import Image
from os.path import dirname, join as pjoin
from collections import defaultdict
from timeit import default_timer as timer

matrix = scipy.io.loadmat('depth_list.mat')
cap = cv2.VideoCapture('DepthVideo.mp4')

ret, frame = cap.read()

while(cap.isOpened()):

	start = timer()

	frame2 = frame[0:480, 0:320]

	print(frame2.shape)

	cv2.imshow('frame2', frame2)

	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

	# testmatrix = np.empty((320,480), dtype = int)

	testmatrix = matrix['depth_list'][17][0:480, 320:640]

	print(len(testmatrix), len(testmatrix[0]))

	end = timer()
	print(end - start)

cap.release()
cv2.destroyAllWindows()