#ifndef PIECE_H
#define PIECE_H

using namespace std;

#include<string.h>
#include<cstdlib>

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

class Pawn: public Piece{
  
  int starting_position[2];
 
public:
  Pawn(int colour, int starting_position[]);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats );
  bool attack(int old_row, int old_column, int new_row, int new_column);
  ~Pawn();
};

class King: public Piece{

public:
  King(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~King();
};

class Rook: public Piece{

  
public:
  Rook(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~Rook();
};

class Bishop: public Piece{


public:
  Bishop(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~Bishop();
};

class Queen: public Piece{

public:
  Queen(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~Queen();
};

class Knight: public Piece{

public:
  Knight(int colour);
  bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats);
  ~Knight();
};


#endif
