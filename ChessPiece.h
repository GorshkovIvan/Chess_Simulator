#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include<string.h>
#include<cstdlib>

using namespace std;

class Piece{

protected:
  
  int colour;
  string name;
  
public:

  Piece(int colour);
  virtual bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats) = 0;
  string get_name();
  int get_colour();
  virtual ~Piece();
};


#endif
