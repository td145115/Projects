import realsense as rs

class signDetection:
	def __init__(self):
		array = [][]

	def getArray(self):
		try:
			pipeline = rs.pipeline()
			pipeline.start()

			while True:
				frames = pipeline.wait_for_frames()
				depth = frames.get_depth_frame()

				if not depth: continue

				for y in range(480):
					for x in range(640):

						# Getting the distance of any particular pixel in the frame
						dist = depth.get_distance(x, y)

						# Narrowing the search range to between 1m and 10m
						if dist > 10000 and dist < 1000:
							array[y][x] = 0
						else:
							array[y][x] = dist

						# This is doing the calculation every 3 columns
						x += 2
						
					# This is doing the calculation every 3 rows
					y += 2
