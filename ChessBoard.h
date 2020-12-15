#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <string>
#include "piece.h"

#define SIZE 8

class ChessBoard{

  Piece* board[SIZE][SIZE];
  int turn_count = 0;
  int king_coordinates[2][2];
  const char* colours[2] = {"White", "Black"};
  
public:

  ChessBoard();
  void setupBoard();
  bool check_input(const char* currentPosition, const char* newPosition);
  void submitMove(const char* currentPosition, const char* newPosition);
  bool turn_to_move(int row, int column);
  bool check_bounds(int old_row, int old_column, int new_row, int new_column);
  bool check_bounds(int row, int column);
  bool simulate_move(int colour, int old_row, int old_column, int new_row, int new_column);
  void move(int old_row, int old_column, int new_row, int new_column, const char* currentPosition, const char* newPosition);
  bool validate_check(int colour, int row, int column, int last_row, int last_column, int blocking_piece[]);
  bool check_or_checkmate(int colour);
  bool stalemate(int colour);
  bool stalemate_try_move(int colour, int old_row, int old_column);
  bool is_check(int colour, int row, int column, int blocking_piece[] = NULL);
  void move_to_free_cell(int old_row, int old_column, int new_row, int new_column);
  void Eat(int old_row, int old_column, int new_row, int new_column);
  void resetBoard();
  bool check_test(int colour);
  bool Checkmate(int king_row, int king_column, int attacking_piece[]);
  bool tryQuitCheck(int king_row, int king_column, int new_row, int new_column);
  bool indentify_potential_attack(int colour, int king_row, int king_column, int last_row, int last_column);
  void convertToInt(int from[], int to[], const char* currentPosition, const char* newPosition);
  void calculate_path_parameters(int old_row, int old_column, int new_row, int new_column, int &gradient, int &column_step, int &row_step, float &path_len);
  bool check_path( int old_row, int old_column, int new_row, int new_column, int blocking_piece[] = NULL);
  void print();
  ~ChessBoard();
};


#endif 
