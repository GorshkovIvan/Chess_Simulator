#include<iostream>
#include"ChessBoard.h"
#include"ChessPiece.h"
#include"string.h"
#include<math.h>
#include<algorithm>
#include"PiecePawn.h"
#include"PieceKing.h"
#include"PieceQueen.h"
#include"PieceRook.h"
#include"PieceBishop.h"
#include"PieceKnight.h"

using namespace std;

ChessBoard::ChessBoard(){

  setupBoard();

}

void ChessBoard::setupBoard(){
  checkmate = false;
  is_stalemate = false;
  turn_count = 0;
  int starting_position[2];

  for(int column = 0; column < SIZE; column++){

    starting_position[0] = 6;
    starting_position[1] = column;
    board[6][column] = new Pawn(0, starting_position);
    starting_position[0] = 1;
    starting_position[1] = column;
    board[1][column] = new Pawn(1, starting_position);

  }
  
  int colour = 1;
  int row = 0;
  
  for(int side = 0; side < 2; side++){

    if(side == 1){
      colour = 0;
      row = 7;
    }
    
    board[row][4] = new King(colour);
    king_coordinates[colour][0] = row;
    king_coordinates[colour][1] = 4;
    board[row][3] = new Queen(colour);
    board[row][0] = new Rook(colour);
    board[row][7] = new Rook(colour);
    board[row][1] = new Knight(colour);
    board[row][6] = new Knight(colour);
    board[row][2] = new Bishop(colour);
    board[row][5] = new Bishop(colour);
    
  }
  
  for(int row = 2; row < 6; row++){
    for(int column = 0; column < SIZE; column++){

      board[row][column] = NULL;

    }

  }

  cout << "A new chess game is started!" << endl;
  
}

void ChessBoard::resetBoard(){

  for(int row = 0; row < SIZE; row++){
    for(int column = 0; column < SIZE; column++){
      
      if(board[row][column] != NULL){

	delete board[row][column];
	board[row][column] = NULL;
	
      }

    }
  
  }

  setupBoard();

}

bool ChessBoard::check_input(const char* currentPosition, const char* newPosition){

  bool correct_input = true;
  
  if(!((currentPosition[0] < 91 && currentPosition[0] > 64) || (currentPosition[0] < 123 && currentPosition[0] > 96))){

    cerr << "The column of the current piece position was entered incorrectly, please use upper or lower case letters from A to H" << endl;
    correct_input = false;

  }

  if(!(currentPosition[1] < 57 && currentPosition[1] > 48)){

    cerr << "The row of the current piece position was entered incorrectly, please use digits from 1 to 8" << endl;
    correct_input = false;
  }

  if(!((newPosition[0] < 91 && newPosition[0] > 64) || (newPosition[0] < 123 && newPosition[0] > 96))){

    cerr << "The column of the new piece position was entered incorrectly, please use upper or lower case letters from A to H" << endl;
    correct_input = false;
  }

  if(!(newPosition[1] < 57 && newPosition[1] > 48)){

    cerr << "The row of the current piece position was entered incorrectly, please use digits from 1 to 8" << endl;
    correct_input = false;
  }

  return correct_input;

}

void ChessBoard::submitMove(const char* currentPosition, const char* newPosition){

  if(!(is_check(0, king_coordinates[0][0], king_coordinates[0][1])) && stalemate(0)){
    cout << colours[0] << " is in stalemate. The game ends as a draw" << endl;
    is_stalemate = true;
  }
  
  if(!(is_check(1, king_coordinates[1][0], king_coordinates[1][1])) && stalemate(1)){
    cout << colours[1] << " is in stalemate. The game ends as a draw" << endl;
    is_stalemate = true;
  }
  
  if(!checkmate && !is_stalemate){
  
    int from[2];
    int to[2];  
    int old_row;
    int old_column;
    int new_row;
    int new_column;

    if(check_input(currentPosition, newPosition)){
      
      convertToInt(from, to, currentPosition, newPosition);
    
      old_row = 7 - from[1];
      old_column = from[0];
      new_row = 7 - to[1];
      new_column = to[0];
      
      if(board[old_row][old_column] != NULL){
	if(check_bounds(old_row, old_column, new_row, new_column) && turn_to_move(old_row, old_column)){

	  move(old_row, old_column, new_row, new_column, currentPosition, newPosition);
    
	}
      }else{

	cerr << "There is no piece at position " << currentPosition << "!" << endl;

      }

    }
  }else{
    cout << "The game has ended! Please reset the board in order to play again!" << endl;
  }
  
  
}

bool ChessBoard::turn_to_move(int row, int column){

  if(board[row][column]->get_colour() == 0 && turn_count % 2 != 0){
    cerr << "It is not White's turn to move!" << endl;
    return false;
  }

  if(board[row][column]->get_colour() == 1 && turn_count % 2 == 0){
    cerr << "It is not Black's turn to move!" << endl;
    return false;
  }

  return true;
}

bool ChessBoard::check_or_checkmate(int colour){

  int blocking_piece[2];
  
  if(is_check(colour, king_coordinates[colour][0], king_coordinates[colour][1], blocking_piece)){

    if(Checkmate(king_coordinates[colour][0], king_coordinates[colour][1], blocking_piece)){
      
      cout << colours[colour] <<" is in checkmate" << endl;
      checkmate = true;
      return true;
    }
    
    else{
	  
      cout << colours[colour] <<" is in check" << endl;
      
      return true;
      
    }
  
  }
    return false;

}

bool ChessBoard::simulate_move(int colour, int old_row, int old_column, int new_row, int new_column){

  int king_row = king_coordinates[colour][0];
  int king_column = king_coordinates[colour][1];
  bool check;
  
  Piece *tmp = board[new_row][new_column];
  move_to_free_cell(old_row, old_column, new_row, new_column);
  check = is_check(colour, king_row, king_column);
  move_to_free_cell(new_row, new_column, old_row, old_column);
  board[new_row][new_column] = tmp;

  return check;


}

void ChessBoard::move(int old_row, int old_column, int new_row, int new_column, const char* currentPosition, const char* newPosition){

    
  bool legal_piece_move;
  bool free_path;
  int moving_colour;
  int rival_colour;
  string moving_piece_name;
  bool move_happened = false;
  
  moving_colour = board[old_row][old_column]->get_colour();
  rival_colour = (moving_colour + 1) % 2;
  moving_piece_name = board[old_row][old_column]->get_name();
  
  if(board[new_row][new_column] == NULL){
    
    legal_piece_move = board[old_row][old_column]-> validate_move(old_row, old_column, new_row, new_column, false);
    free_path = check_path(old_row, old_column, new_row, new_column);
    
    if(legal_piece_move && free_path){
      if(!simulate_move(moving_colour, old_row, old_column, new_row, new_column)){
	cout << colours[moving_colour] << "'s " << moving_piece_name  <<" moves from " << currentPosition << " to " << newPosition << endl;
	move_to_free_cell(old_row, old_column, new_row, new_column);
	move_happened = true;
      }else{
	cout << colours[moving_colour] <<"'s " << moving_piece_name << " cannot move to " << newPosition  << "!" << " It leads to check "  << endl;
      }
      
    }else{
      cout << colours[moving_colour] <<"'s " << moving_piece_name << " cannot move to " << newPosition  << "!"  << endl;
    }
      
  }else{
    
    legal_piece_move = board[old_row][old_column]-> validate_move(old_row, old_column, new_row, new_column, true);
    free_path = check_path(old_row, old_column, new_row, new_column);
    
    if(legal_piece_move && free_path && board[new_row][new_column]->get_colour() == rival_colour && board[new_row][new_column]->get_name() != "King"){
       if(!simulate_move(moving_colour, old_row, old_column, new_row, new_column)){

	 cout << colours[moving_colour] << "'s " << moving_piece_name  <<" moves from " << currentPosition << " to " << newPosition;
	 cout << " taking " << colours[rival_colour] << "'s " << board[new_row][new_column]->get_name() << endl;

	 delete board[new_row][new_column];
	 move_to_free_cell(old_row, old_column, new_row, new_column);
	 move_happened = true;

       }else{
	cout << colours[moving_colour] <<"'s " << moving_piece_name << " cannot move to " << newPosition  << "!" << " It leads to check "  << endl;
      }
          
    }else{
      cout << colours[moving_colour] <<"'s " << board[old_row][old_column]->get_name() << " cannot move to " << newPosition  << "!"  <<endl;
      if (board[new_row][new_column]->get_name() == "King"){

	cout << "King can't be eaten!" << endl;

      }
    }
    
  }

  if(move_happened && board[new_row][new_column]-> get_name() == "King"){

    king_coordinates[moving_colour][0] = new_row;
    king_coordinates[moving_colour][1] = new_column;


  }

  if(move_happened){
    check_or_checkmate(rival_colour);
    turn_count++;
  }
}


bool ChessBoard::stalemate_try_move(int colour, int old_row, int old_column){

  bool check = true;
  bool eat;
  
  for(int new_row = 0; (new_row < SIZE) && check; new_row++){

    for(int new_column = 0; (new_column < SIZE) && check; new_column++){

      if(board[new_row][new_column] == NULL || (board[new_row][new_column]-> get_colour() != colour && board[new_row][new_column]-> get_name() != "King")){
	if(board[new_row][new_column] == NULL){
	
	  eat = false;
	
	}else if(board[new_row][new_column]-> get_colour() != colour && board[new_row][new_column]-> get_name() != "King"){

	  eat = true;

	}
      
	if(board[old_row][old_column]->validate_move(old_row, old_column, new_row, new_column, eat) && check_path(old_row, old_column, new_row, new_column)){
	
	  if(board[old_row][old_column] -> get_name() == "King"){

	    king_coordinates[colour][0] = new_row;
	    king_coordinates[colour][1] = new_column;
	    check = simulate_move(colour, old_row, old_column, new_row, new_column);
	    if(check == false)
	      cout << old_row << "  " << old_column << "  " << new_row << "  " << new_column << endl;
	    king_coordinates[colour][0] = old_row;
	    king_coordinates[colour][1] = old_column;
		      
	  }else{

	    check = simulate_move(colour, old_row, old_column, new_row, new_column);

	  }
	}
      }
    }	    
  }

  return check;
}


bool ChessBoard::stalemate(int colour){

  bool check = true;
  
  for(int old_row = 0; (old_row < SIZE) && check; old_row++){

    for(int old_column = 0; (old_column < SIZE) && check; old_column++){
      
      if(board[old_row][old_column] != NULL && board[old_row][old_column]-> get_colour() == colour){

	check = stalemate_try_move(colour, old_row, old_column);

      }
      
    }
  }

  
  return check;
  
}

void ChessBoard::move_to_free_cell(int old_row, int old_column, int new_row, int new_column){

  board[new_row][new_column] = board[old_row][old_column];
  board[old_row][old_column] = NULL;
     

}


bool ChessBoard::check_bounds(int old_row, int old_column, int new_row, int new_column){

  if((old_row < 0) || (old_row > 7)){

    cerr << "Old position is out of bound chess board size is 8x8" << endl;
    return false;
    
  }

  if((old_column < 0) || (old_column > 7)){
    
    cerr << "Old position is out of bound chess board size is 8x8" << endl;
    
    return false;
    
  }

  if((new_row < 0) || (new_row > 7)){

    cerr << "New position is out of bound chess board size is 8x8" << endl;
    return false;
    
  }

  if((new_column < 0) || (new_column > 7)){

    cerr << "New position is out of bound chess board size is 8x8" << endl;
    return false;
    
  }

  return true;
  
}

bool ChessBoard::check_bounds(int row, int column){

  if((row < 0) || (row > 7))
    return false;

  if((column < 0) || (column > 7))
    return false;
    
 

  return true;
  
}


void ChessBoard::calculate_path_parameters(int old_row, int old_column, int new_row, int new_column, int &gradient, int &column_step, int &row_step, float &path_len){

     
  if(new_column == old_column){
    gradient = 0;
    row_step = (new_row - old_row)/abs(old_row - new_row);
    path_len = sqrt( pow((old_row - new_row), 2.0)+ pow((old_column - new_column), 2.0));
  }else if (new_row == old_row){
    gradient = 0;
    path_len = sqrt( pow((old_row - new_row), 2.0)+ pow((old_column - new_column), 2.0));
    column_step = (new_column - old_column)/abs(old_column - new_column);
  }else{
    row_step = (new_row - old_row)/abs(old_row - new_row);
    gradient = (new_row - old_row)/(new_column - old_column);
    path_len = sqrt( pow((old_row - new_row), 2.0)+ pow((old_column - new_column), 2.0))/sqrt(2.0);
  }


}

bool ChessBoard::check_path(int old_row, int old_column, int new_row, int new_column, int blocking_piece[]){
  
  int coordinates[2] = {old_row, old_column};
  int gradient;
  int column_step = 0;
  int row_step = 0;
  float path_len;
  float rem;
  
  if(new_column == old_column && new_row == old_row)
    return true;

  calculate_path_parameters(old_row, old_column, new_row, new_column, gradient, column_step, row_step, path_len);
    
  rem = remainder(path_len, 1.0);
  
  if(rem != 0.0 || rem != -0.0){
    return true;

  }  
  
  for(float move_count = 0; move_count < path_len - 1; move_count++){

    coordinates[0] = coordinates[0] + row_step;
    coordinates[1] = coordinates[1] + gradient * row_step + column_step;
    if(board[coordinates[0]][coordinates[1]] != NULL){
      if(blocking_piece != NULL){
	blocking_piece[0] = coordinates[0];
	blocking_piece[1] = coordinates[1];
      }
      return false;

    }
  }

  return true;
  
}


bool ChessBoard::validate_check(int colour, int row, int column, int last_row, int last_column, int blocking_piece[]){
  
  bool free_path;
  int piece_coordinates[2];
  
  if(blocking_piece == NULL)
    blocking_piece = piece_coordinates;
  
  free_path = check_path(row, column, last_row, last_column, blocking_piece);

  if(!free_path && (board[blocking_piece[0]][blocking_piece[1]]->get_colour() != colour)){
    if(board[blocking_piece[0]][blocking_piece[1]]->validate_move(blocking_piece[0], blocking_piece[1], row, column, true)){
      
      return true;
    }
  }

  if(free_path && (board[last_row][last_column] != NULL) && (board[last_row][last_column] ->get_colour() != colour)){
    if(board[last_row][last_column]->validate_move(last_row, last_column, row, column, true)){

      return true;
    }
  }

  return false;
  

}

bool ChessBoard::is_check(int colour, int row, int column, int blocking_piece[]){
  
  
  
  /*=============== Checking Row ===================*/
  if(validate_check(colour, row, column, SIZE - 1, column, blocking_piece)){

    return true;
    
  }
  if(validate_check(colour, row, column, 0, column, blocking_piece)){

    return true;
    
  }

   
   /*================= Checking Column ===================*/
  if(validate_check(colour, row, column, row, SIZE - 1, blocking_piece)){
    
    return true;
    
  }
  if(validate_check(colour, row, column, row, 0, blocking_piece)){

    return true;
    
  }
   
  /*================= Checking Diagonal ===================*/
  
  int delta = min(SIZE - 1 - row, SIZE - 1 - column);  
  int last_row = row + delta;
  int last_column = column + delta;
  
  if(validate_check(colour, row, column, last_row, last_column, blocking_piece)){
    
    return true;

  }
  
  delta = max(0 - row, 0 - column);  
  last_row = row + delta;
  last_column = column + delta;

  if(validate_check(colour, row, column, last_row, last_column, blocking_piece)){

    return true;
    
  }
  
  delta = min(abs(SIZE - 1 - row), abs(0 - column));  
  last_row = row + delta;
  last_column = column - delta;
  
  if(validate_check(colour, row, column, last_row, last_column, blocking_piece)){

    return true;
    
  }
  
  delta = min(abs(0 - row), abs(SIZE - 1 - column));  
  last_row = row - delta;
  last_column = column + delta;

  if(validate_check(colour, row, column, last_row, last_column, blocking_piece)){

    return true;
    
  }

  /*================= Checking Knight ===================*/
  int row1, row2;
  int column1, column2;
  for(int i = - 1; i < 2; i = i + 2){

    row1 = row + i;
    column2 = column + i;
    
    for(int j = -2; j < 3; j = j + 4){

      column1 = column + j;
      row2 = row + j;
    
    
      if(check_bounds(row1, column1) && validate_check(colour, row, column, row1, column1, blocking_piece)){
	return true;

      }

      if(check_bounds(row2, column2) && validate_check(colour, row, column, row2, column2, blocking_piece)){
	return true;
      }
    }
  }


  
  return false;

}

bool ChessBoard::Checkmate(int king_row, int king_column, int attacking_piece[]){

  int new_row;
  int new_column;
  
  for(int i = -1; i < 2; i = i + 2){

    new_row = king_row + i;
    new_column = king_column + i;

    if(!tryQuitCheck(king_row, king_column, new_row, king_column))
      return false;
  

    if(!tryQuitCheck(king_row, king_column, king_row, new_column))
      return false;

    if(!tryQuitCheck(king_row, king_column, new_row, new_column))
      return false;
  
    new_row = king_row - i;

    if(!tryQuitCheck(king_row, king_column, new_row, new_column))
      return false;

  }

  int king_colour = board[king_row][king_column]->get_colour();
  int rival_colour = (king_colour + 1) % 2;
  int attacking_row = attacking_piece[0];
  int attacking_column = attacking_piece[1];
  bool check;

  for(int row = 0; row < SIZE; row++){

    for(int column = 0; column < SIZE; column++){

      if(board[row][column] != NULL && board[row][column]->get_colour() != rival_colour && board[row][column]->get_name() != "King"
	 && board[row][column]->validate_move(row, column, attacking_row, attacking_column, true)){

	if(check_path(row, column, attacking_row, attacking_column)){
	  check = simulate_move(king_colour, row, column, attacking_row, attacking_column);

	  if(!check){
	      return false;
	    }


	  }


      }

    }

  }

  if(board[attacking_row][attacking_column]-> get_name() == "Knight"){

    return true;

  }
  
  int gradient;
  int column_step = 0;
  int row_step = 0;
  float path_len;
  int path_row = attacking_row;
  int path_column = attacking_column;
  
  calculate_path_parameters(attacking_row, attacking_column, king_row, king_column, gradient, column_step, row_step, path_len); 
    
  for(float move_count = 0; move_count < path_len - 1; move_count++){

    path_row = path_row + row_step;
    path_column = path_column + gradient * row_step + column_step;
    
    for(int row = 0; row < SIZE; row++){

      for(int column = 0; column < SIZE; column++){

	if(board[row][column] != NULL && board[row][column]->get_colour() != rival_colour && board[row][column]->get_name() != "King"
	   && board[row][column]->validate_move(row, column, path_row, path_column, false)){

	  if(check_path(row, column, path_row, path_column)){
	    check = simulate_move(king_colour, row, column, path_row, path_column);
	    
	    if(!check){
	      
	      return false;
	    }


	  }


	}

      }

    }

  }


  return true;
    
}

bool ChessBoard::tryQuitCheck(int king_row, int king_column, int new_row, int new_column){

  bool check;
  int colour = board[king_row][king_column]->get_colour();

  if(check_bounds(new_row, new_column)){
    if(board[new_row][new_column] == NULL){
 
      king_coordinates[colour][0] = new_row;
      king_coordinates[colour][1] = new_column;
      check = simulate_move(colour, king_row, king_column, new_row, new_column);
      king_coordinates[colour][0] = king_row;
      king_coordinates[colour][1] = king_column;
	
      if(!check){
	return false;
      }
    }else if (board[new_row][new_column]->get_colour() != colour){
      
      king_coordinates[colour][0] = new_row;
      king_coordinates[colour][1] = new_column;
      check = simulate_move(colour, king_row, king_column, new_row, new_column);
      king_coordinates[colour][0] = king_row;
      king_coordinates[colour][1] = king_column;

      if(!check){
	return false;
      }
    }
    
  }
 
  return true;
  
}


void ChessBoard::convertToInt(int from[], int to[], const char* currentPosition, const char* newPosition){
  
  if(currentPosition[0] > 64 && currentPosition[0] < 91)
    from[0] = currentPosition[0] - 65;
  else
    from[0] = currentPosition[0] - 97;
  
  if(newPosition[0] > 64 && newPosition[0] < 91)
    to[0] = newPosition[0] - 65;
  else
    to[0] = newPosition[0] - 97;
  
  from[1] = currentPosition[1] - 49;
  to[1] = newPosition[1] - 49;

}

void ChessBoard::print(){
  string name;
  char column_name;
  if(false){
  cout << "   ";
  for(int column = 0; column < SIZE; column++){
    column_name = 65 + column;
    cout << column_name  << "  ";

  }

  cout << endl;

  for(int column = 0; column < SIZE; column++){

    cout << "____";

  }

  cout << endl;
  
  for(int row = 0; row < SIZE; row++){
    cout << 7 - row + 1 << "| ";
    for(int column = 0; column < SIZE; column++){
      if(board[row][column] != NULL){
	name =  board[row][column]->get_name();
	cout << name[0] << name[1] << " ";
	
      }else{

	 cout << "--" << " ";

      }

    }
    cout << endl;
    
  }
  }
}

ChessBoard::~ChessBoard(){

  for(int row = 0; row < SIZE; row++){
    for(int column = 0; column < SIZE; column++){
      
      if(board[row][column] != NULL){

	delete board[row][column];
	board[row][column] = NULL;
	
      }

    }
  
  }

}

