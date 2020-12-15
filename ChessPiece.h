/*C++ coursework 3 Name: Ivan Gorshkov Date: 15.12.2020 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include<string.h>
#include<cstdlib>

using namespace std;

class Piece{

protected:
  
  int colour;   //Every piece has name and colour
  string name;
  
public:

  /*Virtual Constructor*/
  Piece(int colour);

  
  /*Virtual function that every piece uses to validate its moves */
  virtual bool validate_move(int old_row, int old_column, int new_row, int new_column, bool eats) = 0;

  
  /*Returns Piece name */
  string get_name();

  
  /*Returns piece colour*/
  int get_colour();

  /*Virtual Destructor */
  virtual ~Piece();
  
};


#endif
