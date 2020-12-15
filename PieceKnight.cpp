#include<iostream>
#include<string.h>
#include <stdlib.h>
#include"ChessPiece.h"
#include"PieceKnight.h"

using namespace std;


Knight::Knight(int colour):Piece(colour){
  
  this-> name = "Knight";
}


bool Knight::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  
  if((abs(old_row - new_row) == 1 && abs(old_column - new_column) == 2)||(abs(old_row - new_row) == 2 && abs(old_column - new_column) == 1))
    return true;

  return false;
 
  
}

Knight::~Knight(){}
