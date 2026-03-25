// ==============================================================================
// main.cpp
// ==============================================================================

#include <iostream>
#include <sstream>
#include <string>

#include "checkerboard.hpp"

void demoSaveAndLoad() {
    std::cout << "\n--- Demo: save/load move history ---\n";

    Checkerboard board;
    board.initialConditions();

    try {
        board.play(Position("E7"), Position("E5"), false);
        board.play(Position("E2"), Position("E4"), true);
        board.play(Position("G8"), Position("F6"), false);
    }
    catch (const std::exception& e) {
        std::cout << "Demo setup failed: " << e.what() << "\n";
        return;
    }

    const std::string demoFile = "demo/demo_game.txt";
    board.saveToFile(demoFile);

    Checkerboard restored;
    restored.initialConditions();
    try {
        restored.loadFromFile(demoFile);
    }
    catch (const std::exception& e) {
        std::cout << "Demo load failed: " << e.what() << "\n";
        return;
    }

    std::cout << "Reloaded board from saved history:\n";
    std::cout << restored.toUnicodeString() << "\n";
}

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

    // chessMain();
    demoSaveAndLoad();

    // Checkerboard cb;

    // cb.initialConditions();
    // cb.play(Position("A2"), Position("A4"), true);
    
    // std::cout << cb.toString() << std::endl;
    // std::cout << cb.toUnicodeString() << std::endl;

    return 0;
}
