#include<iostream>
#include<string.h>
#include <stdlib.h>
#include"ChessPiece.h"
#include"PieceQueen.h"

using namespace std;


Queen::Queen(int colour):Piece(colour){
  
  this-> name = "Queen";
}

bool Queen::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  if((new_column != old_column) && (new_row != old_row) && (abs(old_row - new_row) == abs(old_column - new_column)))
  
    return true;

   if(new_column == old_column || new_row == old_row)
    return true;

   return false;
}

Queen::~Queen(){}
