#include<iostream>
#include"piece.h"
#include<string.h>
#include <stdlib.h>
using namespace std;


Piece::Piece(int colour):
  colour(colour){}

string Piece::get_name(){

  return name;

}

int Piece::get_colour(){

  return colour;

}

Piece::~Piece(){}

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

