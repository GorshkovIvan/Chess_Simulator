#ifndef PIECEKING_H
#define PIECEKING_H

#include<string.h>
#include<cstdlib>
#include"ChessPiece.h"

using namespace std;

class King: public Piece{

public:
  
  King(int colour);
  
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  
  ~King();
};

#endif

