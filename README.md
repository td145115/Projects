# Projects
All of the projects that I have completed, both for class as well as on personal time.

My name is Trenton Davis, and I attend Ohio University, with an expected graduation date being December, 2019.

I am a Computer Science major with a Finance minor. I have knowledge of the programming languages C++, Python, and Rust.

# Battleship - Homework 4:

  Two player, Client and Server battleship game. In this game you are playing on a 4x4 board and place one 3 long ship that can be at a diagonal. The first person to get 3 hits wins.

# Decryption - Homework 5:

  Decrypt passwords based on a dictionary. These passwords are salted, and these salts are appended to a possible password and ran through the crypt function, and finally compared to the original password. There are many unused functions in place, because the professor changed the assignment to take into consideration the long runtime of the crypt function. The dictionary words can have up to a three digit number either before or after the word. There are functions in place that account for multiple words with digits in front, the middle, or the end. These functions were no longer required, but felt as if I could leave them in. This program runs in parallel and distributed at the same time. You compile the program using mpicc -fopenmp decrypt.cc -lcrypt.

# Vehicle Testing - PAVE:

  There are many files within this folder, and each will have an explanation to go along with it.
  
  histogramCalc.py: This file calculates a histogram using the matlab library for python. The input for this file is a depth video. The depth video is a file that contains data on the depth of a particular pixel, which is within an range of 1000 to 6000. The camera sees up to 6 meters, so using the histogram, we can see spikes where a cluster of pixels have a similar/the same range. This was used to attempt to write a clustering algorithm, but I got tasked with other things, as it was over the summer and we were attending competitions, so the focus was competition requirements. The input for this class is a depth array, which is the numeric itself mentioned prior, as well as a depth frame.
  
  whiteLineOnGrass.py: This is the line detection that Dylan Wright and I wrote at the IGVC competition because we were in need of a more reliable line detection that worked on grass. This algorithm defines a class, so it is much easier to call functions to do the line detection. The main goal for this project was having a reliable algorithm that did not use a neural network because of the problem we were running in to with time complexity. This class returns the tuples that are right lines, left lines, and horizontal lines. The input for this is an mp4 file.
