#ifndef PIECEBISHOP_H
#define PIECEBISHOP_H

#include<string.h>
#include<cstdlib>
#include"ChessPiece.h"

using namespace std;

class Bishop: public Piece{

public:
  
  Bishop(int colour);
  
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  
  ~Bishop();
};

#endif
