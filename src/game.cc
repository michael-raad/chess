#include "game.h"
using namespace std;

Game::Game(int variant) : variant{ variant } {
  board = make_unique<StandardBoard>(); // For a different variant, type of board constructed depends on variant
  textdisplay = make_unique<TextDisplay>(dynamic_cast<StandardBoard*>(board.get()), board->getNumFile(), board->getNumRank());
  graphicsdisplay = make_unique<GraphicsDisplay>(dynamic_cast<StandardBoard*>(board.get()), board->getNumFile(), board->getNumRank());
  board->addDisplay(textdisplay.get());
  board->addDisplay(graphicsdisplay.get());
}


void Game::addPlayer(unique_ptr<PlayerController> player) {
  players.push_back(move(player));
}


void Game::init() {
  startingColour = Colour::White;
  players.clear();
  board->config();
}


void Game::setup() {
  board->clear();
  board->outputDisplays();
  string line;
  string cmd; // Operation ("+", "-"", "=", "done")
  char piece; // P/p, R/r, N/n, B/b, Q/q, K/k
  char file; // Piece file (a-h for standard board)
  int rank; // Piece rank (1-8 for standard board)
  int fileIndex; // Convert input to index
  int rankIndex; // Convert input to index
  string colour; // Colour to go first

  cout << "Enter \"help\" for list of commands." << endl;

  while (getline(cin, line)) {
    if (line.empty()) { continue; }
    istringstream iss{ line };
    iss >> cmd;

    // Add Piece
    if (cmd == "+") {
      iss >> piece >> file >> rank;
      fileIndex = file - 'a';
      rankIndex = rank - 1;
      if (iss.fail()) {
        cerr << "Error: Invalid Read" << endl;
      }
      else if ('A' <= piece && piece <= 'Z' && board->addPiece('w', piece + ('a' - 'A'), Square{ fileIndex, rankIndex })) { // If adding the (if white) piece to square works
        // If we placed a king, pawn, or rook, we want to consider them touched,
        switch (piece) {
        case 'K':
          dynamic_cast<King*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        case 'P':
          dynamic_cast<Pawn*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        case 'R':
          dynamic_cast<Rook*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        default:
          break;
        }
        // Display the added piece
        board->outputDisplays();
      }
      else if ('a' <= piece && piece <= 'z' && board->addPiece('b', piece, Square{ fileIndex, rankIndex })) { // If adding the (if black) piece to square works 
        switch (piece) {
        case 'k':
          dynamic_cast<King*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        case 'p':
          dynamic_cast<Pawn*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        case 'r':
          dynamic_cast<Rook*>(board->getPieceAt(Square{ fileIndex, rankIndex }))->touch();
          break;
        default:
          break;
        }
        // Display the added piece
        board->outputDisplays();
      }
      else { // Otherwise failure
        cerr << "Error: Invalid Piece or Location" << endl;
      }
    }

    // Remove Piece
    else if (cmd == "-") {
      iss >> file >> rank;
      fileIndex = file - 'a';
      rankIndex = rank - 1;
      if (iss.fail()) {
        cerr << "Error: Invalid Read" << endl;
      }
      else if (!board->removePiece(Square{ fileIndex, rankIndex })) { // If removing the piece at square fails
        cerr << "Error: Invalid Location" << endl;
      }
      else { // Otherwise Success
        board->outputDisplays(); // Tell the displays to output the board state
      }
    }

    // Set the colour to go next
    else if (cmd == "=") {
      iss >> colour;
      if (iss.fail()) {
        cerr << "Error: Invalid Read" << endl;
      }
      else if (colour == "White" || colour == "white") {
        startingColour = Colour::White;
      }
      else if (colour == "Black" || colour == "black") {
        startingColour = Colour::Black;
      }
      else {
        cerr << "Error: Invalid Colour" << endl;
      }
    }

    // Exit setup mode
    else if (cmd == "done") {
      if (board->isValidState()) return; // Board must be in valid state to exit
      else { cerr << "Error: Board is Invalid!" << endl; }
    }

    // Help command
    else if (cmd == "help") {
      cout << "Commands:" << endl;
      cout << "+ [Piece] [Location] -- To add a piece" << endl;
      cout << "- [Location]         -- To remove a piece" << endl;
			cout << "= [Colour]           -- To set colour to play" << endl;
      cout << "done                 -- To exit setup mode" << endl;
			cout << "NOTE: Board must be in valid position to exit setup mode" << endl;
    }

    else {
      cerr << "Error: Invalid Command. Enter \"help\" for a list of commands." << endl;
    }
  }
}


int Game::start() {
  // Select players
  if (variant == 1) { // Different number of players for different variants
    string line, player1, player2, cmd;
    unique_ptr<PlayerController> playerPtr1, playerPtr2;
		cout << "Please provide two players. Enter \"help\" for a list of players" << endl;
    while (getline(cin, line)) {
      istringstream iss{ line };

      // Set player 1
      iss >> player1;
      if (player1 == "human") { playerPtr1 = make_unique<HumanPlayer>(board.get(), Colour::White); }
      else if (player1 == "computer1") { playerPtr1 = make_unique<Computer1>(board.get(), Colour::White); }
      else if (player1 == "computer2") { playerPtr1 = make_unique<Computer2>(board.get(), Colour::White); }
      else if (player1 == "computer3") { playerPtr1 = make_unique<Computer3>(board.get(), Colour::White); }
      else if (player1 == "computer4") { playerPtr1 = make_unique<Computer4>(board.get(), Colour::White); }
      else if (player1 == "computer5") { playerPtr1 = make_unique<Computer5>(board.get(), Colour::White); }
			else if (player1 == "help") {	
				cout << "[WhitePlayer] [BlackPlayer]" << endl;
      	cout << "WhitePlayer and BlackPlayer can be one of:" << endl;
      	cout << '\t' << "- human" << '\t' << '\t' << "- computer1" << endl;
      	cout << '\t' << "- computer2" << '\t' << "- computer3" << endl;
      	cout << '\t' << "- computer4" << '\t' << "- computer5" << endl;
				continue;
			}
      else {
        cerr << "Error: Invalid White Player" << endl;
        continue;
      }

      // Set player 2
      iss >> player2;
      if (player2 == "human") { playerPtr2 = make_unique<HumanPlayer>(board.get(), Colour::Black); }
      else if (player2 == "computer1") { playerPtr2 = make_unique<Computer1>(board.get(), Colour::Black); }
      else if (player2 == "computer2") { playerPtr2 = make_unique<Computer2>(board.get(), Colour::Black); }
      else if (player2 == "computer3") { playerPtr2 = make_unique<Computer3>(board.get(), Colour::Black); }
      else if (player2 == "computer4") { playerPtr2 = make_unique<Computer4>(board.get(), Colour::Black); }
      else if (player2 == "computer5") { playerPtr2 = make_unique<Computer5>(board.get(), Colour::Black); }
      else {
        cerr << "Error: Invalid Black Player" << endl;
        playerPtr1.reset(); // User must re-specify both players again. Reset what we put for player 1
        continue;
      }

      // When both players decided, add them to the game
      addPlayer(move(playerPtr1));
      addPlayer(move(playerPtr2));
      break; // and move on
    }
    if (cin.fail()) { return -2; } // Return error code if input ends
  }

  // Now we perform each player's turn
  board->outputDisplays();
  size_t playerIndex = static_cast<size_t>(startingColour); // start at startingColour's turn
  while (true) {
    TurnResult tr = players[playerIndex]->doTurn(); // perform the turn

    // Player resigns or is checkmated
    if (tr == TurnResult::OUTOFGAME) {
      players.erase(players.begin() + playerIndex); // erase them from player list
      if (players.size() == 1) { // if one player left (this player won)
        return static_cast<int>(players[0]->getColour()); // return int value of colour that won
      }
      playerIndex = playerIndex % players.size(); // Otherwise adjust playerIndex for next turn
    }

    // Player not in check but has no legal moves
    else if (tr == TurnResult::NOLEGALMOVE) {
      if (players.size() == 2) {
        return -1; // -1 Signifies Stalemate
      }
      else {
        // Leaving this to decide on later. We could skip the turn or do something fancy
        playerIndex = ++playerIndex % players.size(); // For now, just move onto next player
      }
    }

    // No move specified, EOF
    else if (tr == TurnResult::ERROR) {
      return -2; // error code
    }

    // When move sccessful, move onto next player
    playerIndex = ++playerIndex % players.size();
  }
}
