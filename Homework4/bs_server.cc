//*****************************************************************
// File: bs_server.cc
// AUthor: Trenton Davis
// Purpose: Battleship Server
//
// returns the clients whether they won or lost, or if there was a hit or miss.
//***************************************************************************
#include <iostream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>
#include <stdlib.h>

//using namespace std;

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
        board_string += "4";
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
 Function: BS()
 Parameters: none
 Return Value: void
 Purpose: This is the referee for the game, and runs the server for the game.
*******************************************/
void BS() {
  boost::asio::io_service my_service;

  // Accept connections on
  // Advertise a service on port 4700
  tcp::acceptor acceptor(my_service, tcp::endpoint(tcp::v4(), 4700));

  tcp::socket socket1(my_service);
  // Wait for a connection from 
  acceptor.accept(socket1);
  // Connection Established!!!

  // Read from Socket 1 until newline
  boost::asio::streambuf buf1;
  int n = boost::asio::read_until( socket1, buf1, '\n' );
  istream is(&buf1);
  string board1;

  getline(is, board1);
  board1 += '\n';

  cout << "Board1: " << board1 << endl;


  //Wait for a connection on Socket #2 
  tcp::socket socket2(my_service);
  acceptor.accept(socket2);
  // Connection Established!!!!
  
  // Read from Socket #2 until newline
  boost::asio::streambuf buf2;
  int n1 = boost::asio::read_until( socket2, buf2, '\n' );
  istream is1(&buf2);
  string board2;

  getline(is1, board2);
  board2 += '\n';

  cout << "Board2: " << board2 << endl;

  // Figure out who won!
  boost::asio::write( socket1, boost::asio::buffer(board2) );
  boost::asio::write( socket2, boost::asio::buffer(board1) );

  int hit1 = 0;
  int hit2 = 0;

  vector<vector<int> > b1 = to_vec(board1);
  vector<vector<int> > b2 = to_vec(board2);
  while(hit1 < 3 && hit2 < 3){
    // cout << "HIT1: " << hit1 << endl;
    // cout << "HIT2: " << hit2 << endl;
    //cout << "HERE" << endl;

    string guess1 = "";
    string guess2 = "";
    string guess1_row_string = "";
    string guess1_col_string = "";
    string guess2_row_string = "";
    string guess2_col_string = "";
    int guess1_row = 0;
    int guess1_col = 0;
    int guess2_row = 0;
    int guess2_col = 0;

    boost::asio::streambuf buf4;
    int n4 = boost::asio::read_until(socket1, buf4, '\n');
    istream is4(&buf4);
    getline(is4, guess1);

    cout << "1 guess: " << guess1 << endl;
    guess1_row_string += guess1[0];
    guess1_col_string += guess1[1];


    boost::asio::streambuf buf6;
    int n6 = boost::asio::read_until(socket2, buf6, '\n');
    istream is6(&buf6);
    getline(is6, guess2);

    cout << "2 guess: " << guess2 << endl;
    guess2_row_string += guess2[0];
    guess2_col_string += guess2[1];


    if(guess1_row_string[0] == '0')
      guess1_row = 0;
    else if(guess1_row_string[0] == '1')
      guess1_row = 1;
    else if(guess1_row_string[0] == '2')
      guess1_row = 2;
    else if(guess1_row_string[0] == '3')
      guess1_row = 3;

    if(guess1_col_string[0] == '0')
      guess1_col = 0;
    else if(guess1_col_string[0] == '1')
      guess1_col = 1;
    else if(guess1_col_string[0] == '2')
      guess1_col = 2;
    else if(guess1_col_string[0] == '3')
      guess1_col = 3;

    if(guess2_row_string[0] == '0')
      guess2_row = 0;
    else if(guess2_row_string[0] == '1')
      guess2_row = 1;
    else if(guess2_row_string[0] == '2')
      guess2_row = 2;
    else if(guess2_row_string[0] == '3')
      guess2_row = 3;

    if(guess2_col_string[0] == '0')
      guess2_col = 0;
    else if(guess2_col_string[0] == '1')
      guess2_col = 1;
    else if(guess2_col_string[0] == '2')
      guess2_col = 2;
    else if(guess2_col_string[0] == '3')
      guess2_col = 3;

    if(b1[guess2_row][guess2_col] == 1){
      hit2++;
      b1[guess2_row][guess2_col] = 2;
    }
    else
      b1[guess2_row][guess2_col] = 3;

    if(b2[guess1_row][guess1_col] == 1){
      hit1++;
      b2[guess1_row][guess1_col] = 2;
    }
    else
      b2[guess1_row][guess1_col] = 3;
    if(hit1 == 3){
      boost::asio::write(socket1, boost::asio::buffer("win\n"));
      boost::asio::write(socket2, boost::asio::buffer("lose\n"));
    }
    else if(hit2 == 3){
      boost::asio::write(socket1, boost::asio::buffer("lose\n"));
      boost::asio::write(socket2, boost::asio::buffer("win\n"));
    }
    else{
      board1 = "";
      board2 = "";
      board2 = to_str(b2);
      board1 = to_str(b1);

      string board2a = board2;
      string board1a = board1;

      board1a += board2;
      board1a += "\n";

      board2a += board1;      
      board2a += "\n";

      boost::asio::write(socket1, boost::asio::buffer(board2a));
      boost::asio::write(socket2, boost::asio::buffer(board1a));
    }
  }
}

/*******************************************
 Function: main()
 Parameters: none
 Return Value: int
 Purpose: This function calls the BS function which runs everything.
*******************************************/
int main()
{
  BS();
  return 0;
}
