#include<iostream>
#include"ChessPiece.h"
#include"PiecePawn.h"
#include<string.h>
#include <stdlib.h>
using namespace std;


Pawn::Pawn(int colour, int starting_position[]):Piece(colour){
  
  this-> name = "Pawn";
  this-> starting_position[0] = starting_position[0];
  this-> starting_position[1] = starting_position[1];
}

bool Pawn::validate_move(int old_row, int old_column, int new_row, int new_column, bool eats){

  if(old_row == new_row && old_column == new_column)
    return false;
  
  if(eats)
    return attack(old_row, old_column, new_row, new_column);
  
  if(colour == 1){
    if(old_row == starting_position[0] && old_column == starting_position[1]){
      if(old_column == new_column && (new_row == old_row + 1 || new_row == old_row + 2)){
	return true;
      }
    
    }else if(old_column == new_column && (new_row == old_row + 1)){

      return true;

    }

    return false;
  }

  if(old_row == starting_position[0] && old_column == starting_position[1]){
    if(old_column == new_column && (new_row == old_row - 1 || new_row == old_row - 2)){
      return true;
    }
    
  }else if(old_column == new_column && (new_row == old_row - 1)){

    return true;

  }

  return false;
  
}

bool Pawn::attack(int old_row, int old_column, int new_row, int new_column){
 
  if(colour == 1){
    
    if((new_column == old_column + 1 || new_column == old_column - 1) && (new_row == old_row + 1)){

      return true;

    }

    return false;
  }

  if((new_column == old_column + 1 || new_column == old_column - 1) && (new_row == old_row - 1)){

    return true;

  }

  return false;
   

}

Pawn::~Pawn(){}
