#include<iostream>
#include"ChessPiece.h"
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

