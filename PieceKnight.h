#ifndef PIECEKNIGHT_H
#define PIECEKNIGHT_H

#include<string.h>
#include<cstdlib>
#include"ChessPiece.h"

using namespace std;

class Knight: public Piece{

public:
  Knight(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~Knight();
};


#endif
