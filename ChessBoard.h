/*C++ coursework 3 Name: Ivan Gorshkov Date: 15.12.2020 */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include "ChessPiece.h"

#define SIZE 8

class ChessBoard{

  Piece* board[SIZE][SIZE];                           //holds pointers to pieces on the chess board
  int turn_count = 0;                                 //Counts the number of moves made
  int king_coordinates[2][2];                         //Tracks coordinates of both kings 
  const char* colours[2] = {"White", "Black"};        //0 is defined as white colour, 1 as black 
  bool checkmate = false;
  bool is_stalemate = false;
  
public:
  
  /*Constructor*/
  ChessBoard(); 
  

  /*Puts board piece on their initial positions. Call from the constructor and resetBoard functions*/
  void setupBoard();
  
  
  /*Checks input validity*/
  bool check_input(const char* currentPosition, const char* newPosition);

  
  /*Converts input parameters to integers*/
  void convertToInt(int from[], int to[], const char* currentPosition, const char* newPosition);

  
  /*Receives input from main and checks that neither checkmate nor stalemate occured in the previous iterations */
  void submitMove(const char* currentPosition, const char* newPosition);

  
  /*Takes coordinates of a piece that is about to move, check its colour and returns true if this colour can move in this iteration */
  bool turn_to_move(int row, int column);

  
  /*Checks if coordinates submitted by the user are inside the board*/
  bool check_bounds(int old_row, int old_column, int new_row, int new_column);

  
  /*Overloaded check_bounds function that can check one cell coordinate*/
  bool check_bounds(int row, int column);

  
  /*Simulates a move by temporarily moving a piece of colour "colour" from its old position to a new one */
  bool simulate_move(int colour, int old_row, int old_column, int new_row, int new_column);

  
  /*Moves a piece if all rules are statisfied, if not, returns warnings*/
  void move(int old_row, int old_column, int new_row, int new_column, const char* currentPosition, const char* newPosition);

  
  /*Takes king's colour and coordinates as an input, checks its row, column and diagonals for a potential attacks, returns true if a king is in check*/
  /*blocking_piece is an optional parameter that is only needed for the Checkmate function, it holds coordinates of a piece that put king in check.  */
  bool is_check(int colour, int row, int column, int blocking_piece[] = NULL);

  
  /*is_check function specifies rows, columns and diagonals that should be tested for checking piece and validate_checks tests whether pieces located */
  /*there can actually attacl the King*/
  bool validate_check(int colour, int row, int column, int last_row, int last_column, int blocking_piece[]);

  
  /*Call is_check and Checkmate function after a move was made*/
  bool check_or_checkmate(int colour);

  
  /*Checks whether a "colour" is in stalemate before every move*/
  bool stalemate(int colour);

  
  /*Called from stalemate. Searches through the board and simulates different moves that can potentially be made by pieces of the specified colour*/
  bool stalemate_try_move(int colour, int old_row, int old_column);

  
  /*Moves a piece to a free cell.*/
  void move_to_free_cell(int old_row, int old_column, int new_row, int new_column);

  
  /*Rests the board by deleting all pieces that the board array was previously pointing to and setting news ones to their initial positions*/
  void resetBoard();

  
  /*Tests for checkmate. Tries to move king, eat the "attacking piece" and put pieces on its way.*/
  bool Checkmate(int king_row, int king_column, int attacking_piece[]);

  
  /*Called from Checkmate fuction, attempts to move a King to quit check. Returns false if managed to quit check.*/
  bool tryQuitCheck(int king_row, int king_column, int new_row, int new_column);

  
  /*Takes two coordinates and determines whether there is a piece between them, if path is free returns true, optional paramter blocking_piece*/
  /*holds the coordinates of the first piece that blocks the path between old and new cell*/
  bool check_path( int old_row, int old_column, int new_row, int new_column, int blocking_piece[] = NULL);

  
  /*Helper function used in check_path and Checkamte, to calculate parameters need to find a way between two cells*/
  void calculate_path_parameters(int old_row, int old_column, int new_row, int new_column, int &gradient, int &column_step, int &row_step, float &path_len);

  
  /*Destructor */
  ~ChessBoard();
};


#endif 
