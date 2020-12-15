#include<iostream>
#include<string.h>
#include <stdlib.h>
#include"ChessPiece.h"
#include"PieceRook.h"

using namespace std;


Rook::Rook(int colour):Piece(colour){
  
  this-> name = "Rook";
}

bool Rook::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  
  if(new_column == old_column || new_row == old_row)
    return true;

  return false;
 
  
}

Rook::~Rook(){}
