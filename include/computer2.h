#ifndef __COMPUTER2_H__
#define __COMPUTER2_H__
#include "playercontroller.h"

class Computer2 : public PlayerController {
public:
  // Construtor
  Computer2(Board* board, Colour colour);

  // Makes Computer2 make one turn
  TurnResult doTurn() override;
};

#endif

