//****************************************************
// File:bs_client.cc
// Author: Trenton Davis
// Purpose: play battleship over the network.
// Connects to bs server.
// bs server acts as referee.
// returns whether you won-lost or hit or miss
//
//**************************************************************************
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <stdlib.h>
using namespace std;
using boost::asio::ip::tcp;

/*******************************************
 Function: to_string(vector<vector<int> > &board)
 Parameters: vector<vector<int> > & board
 Return Value: string
 Purpose: This function converts a board into a string.
*******************************************/
string to_str(vector<vector<int> > &board){
  string board_string = "";
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(board[i][j] == 0)
        board_string += "0";
      else if(board[i][j] == 1)
        board_string += "1";
      else if(board[i][j] == 2)
        board_string += "2";
      else if(board[i][j] == 3)
        board_string += "3";
      else
        board_string == "4";
    }
  }
  return board_string;
}

/*******************************************
 Function: to_vec(string &board_string)
 Parameters: string &board_string
 Return Value: vector<vector<int> >
 Purpose: This function converts a string of integers to a board
          starting from the beginning of the string.
*******************************************/
vector<vector<int> > to_vec(string &board_string){
  vector<vector<int> > board;
  for(int i = 0; i < 4; i++){
    vector<int> t1;
    for(int j = 0; j < 4; j++){
      if(board_string[4 * i + j] == '0')
        t1.push_back(0);
      else if(board_string[4 * i + j] == '1')
        t1.push_back(1);
      else if(board_string[4 * i + j] == '2')
        t1.push_back(2);
      else if(board_string[4 * i + j] == '3')
        t1.push_back(3);
      else
        t1.push_back(4);
    }
    board.push_back(t1);
  }
  return board;
}

/*******************************************
 Function: to_vec2(string &board_string)
 Parameters: string &board_string
 Return Value: vector<vector<int> >
 Purpose: This function converts a string of integers to a board
          starting from the beginning of the second board that is 
          in the string.
*******************************************/
vector<vector<int> > to_vec2(string &board_string){
  vector<vector<int> > board;
  for(int i = 4; i < 8; i++){
    vector<int> t1;
    for(int j = 0; j < 4; j++){
      if(board_string[4 * i + j] == '0')
        t1.push_back(0);
      else if(board_string[4 * i + j] == '1')
        t1.push_back(1);
      else if(board_string[4 * i + j] == '2')
        t1.push_back(2);
      else if(board_string[4 * i + j] == '3')
        t1.push_back(3);
      else
        t1.push_back(4);
    }
    board.push_back(t1);
  }
  return board;
}

/*******************************************
 Function: draw_top_matrix(vector<Vector<int> > &board, int cur_row, int cur_col)
 Parameters: vector<vector<int> > &board
             int cur_row
             int cur_col
 Return Value: void
 Purpose: This function draws a single board.
*******************************************/
void draw_top_matrix(vector<vector<int> > &board,int cur_row,int cur_col) {
  move(1,0);
  printw("Your Board:");
  for(int j=0;j<4;j++) {
    move(2,2*j);
    printw("+-");
  }
  move(2,2*4);
  printw("+");

  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      move(2*i+3,2*j);
      printw("|");
      move(2*i+3,2*j+1);
      if (board[i][j] == 0) {
        printw(" ");
      } 
      else {
        printw("X");
      }
    }
    move(2*i+3,2*4);
    printw("|");
    for (int j=0;j<4;j++) {
      move(2*i+4,2*j);
      printw("+-");
    }
    move(2*i+4,2*4);
    printw("+");
  }
  move(2*cur_row+3,2*cur_col+1);
}

/*******************************************
 Function: draw_top_matrix(vector<Vector<int> > &board, vector<vector<int> > &board2, int cur_row, int cur_col)
 Parameters: vector<vector<int> > &board
             vector<vector<int> > &board2
             int cur_row
             int cur_col
 Return Value: void
 Purpose: This function draws the players board with the opponents moves, as well as the opponents board
          with their choice.
*******************************************/
void draw_both_matrix(vector<vector<int> > &board, vector<vector<int> > &board2, int cur_row, int cur_col) {
  move(1,0);
  printw("Your Board:");
  for(int j=0;j<4;j++) {
    move(2,2*j);
    printw("+-");
  }
  move(2,2*4);
  printw("+");

  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      move(2*i+3,2*j);
      printw("|");
      move(2*i+3,2*j+1);
      if (board[i][j] == 0)
        printw(" ");
      else if(board[i][j] == 1)
        printw("X");
      else if(board[i][j] == 2)
        printw("H");
      else if(board[i][j] == 3)
        printw("M");
      else
        printw(" ");
    }
    move(2*i+3,2*4);
    printw("|");
    for (int j=0;j<4;j++) {
      move(2*i+4,2*j);
      printw("+-");
    }
    move(2*i+4,2*4);
    printw("+");
  }
  move(2*cur_row+3,2*cur_col+1);


  move(14, 0);
  printw("Their Board:");
  for(int j=0;j<4;j++) {
    move(15,2*j);
    printw("+-");
  }
  move(15,2*4);
  printw("+");
  for (int i=0;i<4;i++) {
    for (int j=0;j<4;j++) {
      move(2*i+16,2*j);
      printw("|");
      move(2*i+16,2*j+1);
      if (board2[i][j] == 0)
        printw(" ");
      else if(board2[i][j] == 1)
        printw(" ");
      else if(board2[i][j] == 2)
        printw("H");
      else if(board2[i][j] == 3)
        printw("M");
      else
        printw(" ");
    }
    move(2*i+16,2*4);
    printw("|");
    for (int j=0;j<4;j++) {
      move(2*i+17,2*j);
      printw("+-");
    }
    move(2*i+17,2*4);
    printw("+");
  }
  move(2*cur_row+16,2*cur_col+1);
}

/*******************************************
 Function: main(int argc, char *argv[])
 Parameters: int argc
             char *argv[]
 Return Value: int
 Purpose: This function runs the program.
*******************************************/
int main(int argc, char *argv[]) {
  int rows;
  int cols;
  int cur_row=0;
  int cur_col=0;
  int ch;
  bool placed = false;
  int temp = 0;

  cout << "X args " << argc << endl;
  cout << "server " << argv[1] << endl;
  cout << "port " << argv[2] << endl; 

  vector<vector<int> > board;
  for (int i=0;i<4;i++) {
    vector<int> t;
    for (int j=0;j<4;j++) {
      t.push_back(0);
    }
    board.push_back(t);
  }

  int piece_count = 0;
  // Screen initialization
  initscr();
  // Clear the screen
  clear();
  // Get the size of the window!
  getmaxyx(stdscr,rows,cols);
  cbreak();  // Pass all characters to this program!
  keypad(stdscr, TRUE); // Grab the special keys, arrow keys, etc.
  // Paint the row and column markers.
  //paint_markers(rows,cols,10,0,0);
  // Redraw the screen.
  refresh();
  draw_top_matrix(board,0,0);
  // I/O Loop....
  // Stop when the q Key is hit.
  //
  while((ch = getch())!='q' && placed == false){
    switch (ch) {
    case ' ':
      board[cur_row][cur_col]=1;
      draw_top_matrix(board,cur_row,cur_col);
      piece_count++;
      // Redraw the screen.
      refresh();
      placed = true;
      break;
    case KEY_RIGHT:
      cur_col++;
      cur_col%=4;
      draw_top_matrix(board,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    case KEY_LEFT:
      cur_col--;
      cur_col = (4+cur_col)%4;
      draw_top_matrix(board,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    case KEY_UP:
      cur_row--;
      cur_row=(4+cur_row) % 4;
      draw_top_matrix(board,cur_row,cur_col);
      //      paint_markers(rows,cols,10,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    case KEY_DOWN:
      cur_row++;
      cur_row%=4 + 2;
      draw_top_matrix(board,cur_row,cur_col);
            //paint_markers(rows,cols,10,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    }
    if(piece_count == 1)
      break;
  }

  clear();
  draw_top_matrix(board, 0, 0);

  if(cur_col == 0 || cur_col == 1){
    board[cur_row][cur_col + 1] = 1;
    board[cur_row][cur_col + 2] = 1;
  }
  else if(cur_col == 2 || cur_col == 3){
    board[cur_row][cur_col - 1] = 1;
    board[cur_row][cur_col - 2] = 1;
  }

  clear();
  draw_top_matrix(board,0,0);
  refresh();

  while((ch = getch()) != ' '){
    if(cur_row < 2 && cur_col < 2){
      switch (ch){
        case KEY_RIGHT:
          if(temp == 0){
            board[cur_row][cur_col + 1] = 0;
            board[cur_row][cur_col + 2] = 0;
            board[cur_row + 1][cur_col + 1] = 1;
            board[cur_row + 2][cur_col + 2] = 1;
            temp = 1;
            break;
          }
          else if(temp == 1){
            board[cur_row + 1][cur_col + 1] = 0;
            board[cur_row + 2][cur_col + 2] = 0;
            board[cur_row + 1][cur_col] = 1;
            board[cur_row + 2][cur_col] = 1;
            temp = 2;
            break;
          }
          else if(temp == 2){
            board[cur_row + 1][cur_col] = 0;
            board[cur_row + 2][cur_col] = 0;
            board[cur_row][cur_col + 1] = 1;
            board[cur_row][cur_col + 2] = 1;
            temp = 0;
            break;
          }
      }
    }
    else if(cur_row >= 2 && cur_col < 2){
      switch (ch){
        case KEY_RIGHT:
          if(temp == 0){
            board[cur_row][cur_col + 1] = 0;
            board[cur_row][cur_col + 2] = 0;
            board[cur_row - 1][cur_col] = 1;
            board[cur_row - 2][cur_col] = 1;
            temp = 1;
            break;
          }
          if(temp == 1){
            board[cur_row - 1][cur_col] = 0;
            board[cur_row - 2][cur_col] = 0;
            board[cur_row - 1][cur_col + 1] = 1;
            board[cur_row - 2][cur_col + 2] = 1;
            temp = 2;
            break;
          }
          if(temp == 2){
            board[cur_row - 1][cur_col + 1] = 0;
            board[cur_row - 2][cur_col + 2] = 0;
            board[cur_row][cur_col + 1] = 1;
            board[cur_row][cur_col + 2] = 1;
            temp = 0;
            break;
          }
      }
    }
    else if(cur_row >= 2 && cur_col >= 2){
      switch (ch){
        case KEY_RIGHT:
          if(temp == 0){
            board[cur_row][cur_col - 1] = 0;
            board[cur_row][cur_col - 2] = 0;
            board[cur_row - 1][cur_col - 1] = 1;
            board[cur_row - 2][cur_col - 2] = 1;
            temp = 1;
            break;
          }
          else if(temp == 1){
            board[cur_row - 1][cur_col - 1] = 0;
            board[cur_row - 2][cur_col - 2] = 0;          
            board[cur_row - 1][cur_col] = 1;
            board[cur_row - 2][cur_col] = 1;  
            temp = 2;
            break;
          }
          else if(temp == 2){
            board[cur_row - 1][cur_col] = 0;
            board[cur_row - 2][cur_col] = 0;
            board[cur_row][cur_col - 1] = 1;
            board[cur_row][cur_col - 2] = 1;
            temp = 0;
            break;
          }
      }
    }
    else if(cur_row < 2 && cur_col >= 2){
      switch (ch){
        case KEY_RIGHT:
          if(temp == 0){
            board[cur_row][cur_col - 1] = 0;
            board[cur_row][cur_col - 2] = 0;
            board[cur_row + 1][cur_col] = 1;
            board[cur_row + 2][cur_col] = 1;
            temp = 1;
            break;
          }
          else if(temp == 1){
            board[cur_row + 1][cur_col] = 0;
            board[cur_row + 2][cur_col] = 0;
            board[cur_row + 1][cur_col - 1] = 1;
            board[cur_row + 2][cur_col - 2] = 1;
            temp = 2;
            break;
          }
          else if(temp == 2){
            board[cur_row + 1][cur_col - 1] = 0;
            board[cur_row + 2][cur_col - 2] = 0;
            board[cur_row][cur_col - 1] = 1;
            board[cur_row][cur_col - 2] = 1;
            temp = 0;
            break;
          }
      }
    }
    clear();
    draw_top_matrix(board,0,0);
    refresh();
  }

  clear();
  draw_top_matrix(board,0,0);
  refresh();

  int portno = atoi(argv[2]);
  // Standard boost code to connect to a server.
  // Comes from the boost tutorial
  boost::asio::io_service my_service;

  tcp::resolver resolver(my_service);
  // Find the server/port number.
  //  tcp::resolver::results_type endpoints = resolver.resolve(argv[2], argv[3]);

  tcp::socket socket(my_service);
  
  string board_string = to_str(board);

  socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(argv[1]),portno));
  
  string msg;
  msg = board_string;
  msg+= "\n";
  boost::asio::write( socket, boost::asio::buffer(msg) );

  clear();
  draw_top_matrix(board,0,0);
  // Get the response from the server!
  clear();

  boost::asio::streambuf buf2;
  boost::asio::read_until( socket, buf2, "\n" );
  string answer = boost::asio::buffer_cast<const char*>(buf2.data());

  vector<vector<int> > board2 = to_vec(answer);
  // clear();
  // draw_top_matrix(board2,0,0);
  // refresh();

  bool winner = false;
  bool you_won = false;

  clear();
  draw_both_matrix(board, board2, 0, 0);
  refresh();
  while(winner == false){
    clear();
    draw_both_matrix(board,board2,0,0);
    refresh();
    move(16,1);
    cur_row = 0;
    cur_col = 0;
    int guess_row = 0;
    int guess_col = 0;
    while((ch = getch()) != ' '){
      switch(ch){
        case KEY_RIGHT:
          cur_col++;
          cur_col%=4;
          draw_both_matrix(board,board2,cur_row,cur_col);
          // Redraw the screen.
          refresh();
          break;
        case KEY_LEFT:
          cur_col--;
          cur_col = (4+cur_col)%4;
          draw_both_matrix(board,board2,cur_row,cur_col);
          // Redraw the screen.
          refresh();
          break;
        case KEY_UP:
          cur_row -= 1;
          cur_row=(4+cur_row) % 4;
          draw_both_matrix(board,board2,cur_row,cur_col);
          //      paint_markers(rows,cols,10,cur_row,cur_col);
          // Redraw the screen.
          refresh();
          break;
        case KEY_DOWN:
          cur_row++;
          cur_row%=4 + 2;
          draw_both_matrix(board,board2,cur_row,cur_col);
                //paint_markers(rows,cols,10,cur_row,cur_col);
          // Redraw the screen.
          refresh();
          break;
      }
    }

    guess_row = cur_row;
    guess_col = cur_col;
    string guess_row_string = "";
    string guess_col_string = "";
    if(guess_row == 0)
      guess_row_string = "0";
    else if(guess_row == 1)
      guess_row_string = "1";
    else if(guess_row == 2)
      guess_row_string = "2";
    else if(guess_row == 3)
      guess_row_string = "3";

    if(guess_col == 0)
      guess_col_string = "0\n";
    else if(guess_col == 1)
      guess_col_string = "1\n";
    else if(guess_col == 2)
      guess_col_string = "2\n";
    else if(guess_col == 3)
      guess_col_string = "3\n";

    //this is for testing purposes.
    
    //cout << "Row: " << guess_row + 1 << endl;
    //cout << "Col: " << guess_col + 1 << endl;
    //cout << answer << endl;
    //cout << board2[0][0] << endl; 

    string guess = guess_row_string + guess_col_string;

    boost::asio::write(socket, boost::asio::buffer(guess));

    string answer1 = "";

    boost::asio::streambuf buf3;
    int n3 = boost::asio::read_until(socket, buf3, '\n');
    istream is3(&buf3);
    getline(is3, answer1);

    board2 = to_vec(answer1);
    board = to_vec2(answer1);

    if(answer1 == "lose"){
	clear();
	move(0,0);
        printw("you lose...");
	move(1,0);
	printw("Press q to quit");
	refresh();
      while((ch = getch()) != 'q'){
	clear();
	move(0,0);
        printw("you lose...");
	move(1,0);
	printw("Press q to quit");
	refresh();
      }
      exit(0);
    }
    else if(answer1 == "win"){
	clear();
	move(0,0);
        printw("YOU WON!!!!!!!");
	move(1,0);
	printw("Press q to quit");
	refresh();
      while((ch = getch()) != 'q'){
	clear();
	move(0,0);
        printw("YOU WON!!!!!!!");
	move(1,0);
	printw("Press q to quit");
	refresh();
      }
      exit(0);
    }
    else{
      vector<vector<int> > board2 = to_vec(answer);
      clear();
      draw_both_matrix(board,board2,0,0);
      refresh();
    }
  }
}
  
