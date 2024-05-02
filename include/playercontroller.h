#ifndef __PLAYERCONTROLLER_H__
#define __PLAYERCONTROLLER_H__
#include <vector>
#include <random>
#include <map>
#include <iostream>
#include "board.h"
#include "colour.h"
#include "turnresult.h"

class PlayerController {

  // Private fields 
  Board* board;
  Colour colour;

protected:
  // Returns the board this player is playing on
  Board* getBoard() const;

  int getRandomIndex(int index) const;
  
public:
  // Constructor & Destructor
  PlayerController(Board* board, Colour colour);
  virtual ~PlayerController() = default;

  // Returns colour the player is playing as
  Colour getColour();

  // Perform this player's turn
  virtual TurnResult doTurn() = 0;
};


#endif
