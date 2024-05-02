#include <iostream>
#include <string>
#include "game.h"

using namespace std;

// Helper function to print the score of a standard game (variant 1)
void printScoreStandard(float whiteScore, float blackScore) {
  cout << "Final Score:" << endl;
  cout << "White: " << whiteScore << endl;
  cout << "Black: " << blackScore << endl;
}

// Main
int main(int argc, char* argv[]) {
  bool enableVariant = false;

  // Check if --enablevariant flag is provided
	for (int i = 1; i < argc; ++i) {
		if (string(argv[i]) == "--enablevariant") {
			enableVariant = true;
		}
	}

  // Can add more colours later
  float whiteScore = 0;
  float blackScore = 0;
  int variant; // Determines which board to play on and num players

  // If bonus is enabled, prompt the user for the variant
  if (enableVariant) {
    while (true) {
      cout << "Enter board type:" << endl;
			cout << "\t'1' for a standard 8x8 board" << endl; // Room for other variants
      cin >> variant;
      if (variant < 1 || variant > 1) { // change bounds when other variants made
        cerr << "invalid variant" << endl;;
      }
      else {
        break;
      }
    }
  }
  else {
    // If bonus is not enabled, set standard board
    variant = 1;
  }

  // Main loop
  string command;
  unique_ptr<Game> game = make_unique<Game>(variant); // Make a game
  while (!cin.fail()) {
    game->init(); // Everytime we finish a game, reset players and reconfigure board

    while (cout << "Enter command: " && cin >> command) {

      // Start the game
      if (command == "game") {
        int result = game->start(); // Run the game and store the result
        if (variant == 1) { // Can add other scoring results for different variants
          if (result == -1) { // -1 --> draw
            whiteScore += 0.5;
            blackScore += 0.5;
            cout << "Stalemate!" << endl;
          }
          else if (result == 0) { // 0 --> White Won
            ++whiteScore;
            cout << "White Wins!" << endl;
          }
          else if (result == 1) { // 1 --> Black Won
            ++blackScore;
            cout << "Black Wins!" << endl;
          }
          else { break; } // Any other result --> error result (EOF)
          printScoreStandard(whiteScore, blackScore); // Print score after a game ends
        }
        break;
      }

      // Setup the board
      else if (command == "setup") {
        game->setup(); // Enter setup mode
      }
      else if (command == "help") {
        cout << "Commands:" << endl;
        cout << "setup       -- To enter setup mode" << endl;
        cout << "game        -- To start a game" << endl;
      }
      else {
        cerr << "Invalid command. Enter \"help\" for list of commands." << endl;
      }
    }
  }

  // Print scoreboard after receiving EOF
  if (variant == 1) {
    cout << endl;
    printScoreStandard(whiteScore, blackScore);
  }
}
