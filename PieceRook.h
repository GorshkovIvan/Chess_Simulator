#ifndef PIECEROOK_H
#define PIECEROOK_H

#include<string.h>
#include<cstdlib>
#include"ChessPiece.h"

using namespace std;

class Rook: public Piece{
  
public:
  
  Rook(int colour);
  
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  
  ~Rook();
};

#endif
