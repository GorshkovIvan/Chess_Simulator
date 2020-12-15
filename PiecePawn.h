#ifndef PIECEPAWN_H
#define PIECEPAWN_H

using namespace std;
#include "ChessPiece.h"
#include<string.h>
#include<cstdlib>

class Pawn:public Piece{
  
  int starting_position[2];
 
public:

  /*In addition to colour, the constructor takes a pawn startig position, this is needed to check whther a pawn can move two cells forwards */
  Pawn(int colour, int starting_position[]);

  
  /*If eats is true, calls the attack funtion */
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats );

  
  /*Check if a pawn can eat from old to new coordinate*/
  bool attack(int old_row, int old_column, int new_row, int new_column);

  
  ~Pawn();
};

#endif
