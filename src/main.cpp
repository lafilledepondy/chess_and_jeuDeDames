// ==============================================================================
// main.cpp
// ==============================================================================

#include <iostream>
#include <sstream>
#include <string>

#include "checkerboard.hpp"

void chessMain() {
    Checkerboard cb;
    cb.initialConditions();

    std::string input;
    bool turnBlack = false; // white starts

    while (true) {
        std::cout << cb.toUnicodeString() << std::endl;
        std::cout << (turnBlack ? "Black" : "White") << " move: \n> ";
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
        }
        if (input == "undo") {
            if (cb.undoLastMove()) {
                turnBlack = !turnBlack;
                std::cout << "~~~Last move undone\n\n";
            } else {
                std::cout << "~~~No move to undo\n\n";
            }
            continue;
        }

        std::istringstream iss(input);
        std::string startStr, endStr;

        if (!(iss >> startStr >> endStr)) {
            std::cout << "Invalid format. Use: `D6 D4`\n";
            continue;
        }

        try {
            Position start(startStr);
            Position end(endStr);

            cb.play(start, end, turnBlack);
            turnBlack = !turnBlack; // switch player
            // spacing from the previous player
            std::cout << "\n";
            std::cout << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Invalid move: " << e.what() << std::endl;
        }
    }
}

int main() {

    for(int i = 0; i < 100; ++i) {
        std::cout << "\n";
    }    
    std::cout << "+==============================================================+" << std::endl;
    std::cout << "|                       CHESS & CHECKERS                       |" << std::endl;
    std::cout << "+==============================================================+" << std::endl;

    chessMain();

    // Checkerboard cb;

    // cb.initialConditions();
    // cb.play(Position("A2"), Position("A4"), true);
    
    // std::cout << cb.toString() << std::endl;
    // std::cout << cb.toUnicodeString() << std::endl;

    Checkerboard board;
    board.initialConditions();

    // simulate some moves
    board.play(Position("E2"), Position("E4"), false);
    board.play(Position("E7"), Position("E5"), true);

    // save
    board.saveToFile("demo/demo_game.txt");

    // reload fresh game
    Checkerboard newBoard;
    newBoard.initialConditions();

    newBoard.loadFromFile("demo/dummy_game.txt");

    std::cout << newBoard.toString() << std::endl;

    return 0;
}
