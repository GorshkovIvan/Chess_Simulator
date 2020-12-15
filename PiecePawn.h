#ifndef PIECEPAWN_H
#define PIECEPAWN_H

using namespace std;
#include "ChessPiece.h"
#include<string.h>
#include<cstdlib>

class Pawn:public Piece{
  
  int starting_position[2];
 
public:
  Pawn(int colour, int starting_position[]);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats );
  bool attack(int old_row, int old_column, int new_row, int new_column);
  ~Pawn();
};

#endif
