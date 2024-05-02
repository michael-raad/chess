#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <sstream>
#include <string>
#include "standardboard.h"
#include "colour.h"
#include "square.h"
#include "humanplayer.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"
#include "computer4.h"
#include "computer5.h"
#include "turnresult.h"
#include "window.h"

class Game {
  std::unique_ptr<Board> board; // Owns a Board
  std::vector<std::unique_ptr<PlayerController>> players; // List of players in the game
  std::unique_ptr<TextDisplay> textdisplay;
  std::unique_ptr<GraphicsDisplay> graphicsdisplay;
  std::unique_ptr<Xwindow> xwindow;
  int variant; // Variant of chess being played
  Colour startingColour = Colour::White; // Colour to go first

  // adds the player to vector of players.
  void addPlayer(std::unique_ptr<PlayerController> player);

public:

  // Constructor & Destructor
  Game(int variant);
  ~Game() = default;


  // Resets the Game to default state (White's turn, clears players, board reconfigured to default).
  void init();

  // Enters setup mode, takes in input from cin and configurs board. 
  //  Board must be in valid state before exiting.
  void setup();

  // Starts game based on the game variant. Sets players and cycles through 
  //  them to perform thier turns.
  int start();
};

#endif
