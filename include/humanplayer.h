#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__
#include "playercontroller.h"

class HumanPlayer : public PlayerController {
public:
  // Constructor
  HumanPlayer(Board* board, Colour colour);

  // Perform's human's turn (takes input from cin)
  TurnResult doTurn();
};

#endif
