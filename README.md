# Projects
All of the projects that I have completed, both for class as well as on personal time.

My name is Trenton Davis, and I attend Ohio University, with an expected graduation date being December, 2019.

I am a Computer Science major with a Finance minor. I have knowledge of the programming languages C++, Python, and Rust.

# Battleship - Homework 4:

  Two player, Client and Server battleship game. In this game you are playing on a 4x4 board and place one 3 long ship that can be at a diagonal. The first person to get 3 hits wins.

# Decryption - Homework 5:

  Decrypt passwords based on a dictionary. These passwords are salted, and these salts are appended to a possible password and ran through the crypt function, and finally compared to the original password. There are many unused functions in place, because the professor changed the assignment to take into consideration the long runtime of the crypt function. The dictionary words can have up to a three digit number either before or after the word. There are functions in place that account for multiple words with digits in front, the middle, or the end. These functions were no longer required, but felt as if I could leave them in. This program runs in parallel and distributed at the same time. You compile the program using mpicc -fopenmp decrypt.cc -lcrypt.
