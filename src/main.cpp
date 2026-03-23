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
        std::cout << cb.toString() << std::endl;
        std::cout << (turnBlack ? "Black" : "White") << " move: \n> ";
        std::getline(std::cin, input);

        if (input == "quit") {
            break;
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
            for(int i = 0; i < 3; ++i) {
                std::cout << "\n";
            }
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

    // std::cout << cb.toString() << std::endl;
    

     return 0;
}
