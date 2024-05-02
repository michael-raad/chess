#ifndef __COMPUTER5_H__
#define __COMPUTER5_H__
#include "playercontroller.h"

class Computer5 : public PlayerController {
  int depth = 2;
public:
  // Constructor
  Computer5(Board* board, Colour colour);
  
  // Makes Computer5 make one turn
  TurnResult doTurn() override;
};

#endif

