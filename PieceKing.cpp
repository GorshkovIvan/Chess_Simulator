#include<iostream>
#include<string.h>
#include <stdlib.h>
#include"PieceKing.h"
#include"ChessPiece.h"

using namespace std;


King::King(int colour):Piece(colour){
  
  this-> name = "King";
 
}

bool King::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  if(abs(old_row - new_row) <= 1 && abs(old_column - new_column) <= 1)
    return true;

  return false;
 
  
}

King::~King(){}

