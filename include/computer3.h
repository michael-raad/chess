#ifndef __COMPUTER3_H__
#define __COMPUTER3_H__
#include "playercontroller.h"

class Computer3 : public PlayerController {
public:
  // Constructor
  Computer3(Board* board, Colour colour);

  // Makes Computer2 make one turn
  TurnResult doTurn() override;
};

#endif

