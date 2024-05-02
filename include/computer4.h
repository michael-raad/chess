#ifndef __COMPUTER4_H__
#define __COMPUTER4_H__
#include "playercontroller.h"

class Computer4 : public PlayerController {
public:
  // Constructor
  Computer4(Board* board, Colour colour);
  
  // Makes Computer4 make one turn
  TurnResult doTurn() override;
};

#endif

