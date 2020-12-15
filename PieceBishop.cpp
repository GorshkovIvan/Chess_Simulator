#include<iostream>
#include"ChessPiece.h"
#include<string.h>
#include <stdlib.h>
#include"PieceBishop.h"

using namespace std;

Bishop::Bishop(int colour):Piece(colour){
  
  this-> name = "Bishop";
}

bool Bishop::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  if((new_column != old_column) && (new_row != old_row) && (abs(old_row - new_row) == abs(old_column - new_column)))
    return true;

  return false;
 
  
}

Bishop::~Bishop(){}
