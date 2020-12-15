#ifndef PIECEQUEEN_H
#define PIECEQUEEN_H

#include<string.h>
#include<cstdlib>
#include"ChessPiece.h"

using namespace std;

class Queen: public Piece{

public:
  
  Queen(int colour);
  
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  
  ~Queen();
  
};

#endif
