// ==============================================================================
// main.cpp
// ==============================================================================

#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "checkerboard.hpp"

void replaySavedGame(const std::string& filePath) {
    Checkerboard replayBoard;
    replayBoard.initialConditions();

    // 
    const std::vector<Checkerboard::ReplayMove> moves = replayBoard.readMovesFromFile(filePath);
    if (moves.empty()) {
        std::cout << "No replayable move found in: " << filePath << "\n";
        return;
    }

    std::size_t currentMove = 0;
    std::string command;

    std::cout << "\nReplay controls: n=next, p=previous, a=autoplay, q=quit\n";
    while (true) {
        std::cout << replayBoard.toUnicodeString() << "\n";
        std::cout << "Replay move " << currentMove << "/" << moves.size() << " > ";
        std::getline(std::cin, command);

        if (command == "q") {break;} // quit

        if (command == "n") {
            // replay ended && n
            if (currentMove >= moves.size()) {
                std::cout << "End of replay reached.\n";
                continue;
            }
            // play next move
            const Checkerboard::ReplayMove& move = moves[currentMove];
            try {
                replayBoard.play(move.from, move.to, move.turnBlack);
                ++currentMove;
            }
            // error handling for invalid move in the replay file
            catch (const std::exception& e) {
                std::cout << "Replay stopped on invalid move: " << e.what() << "\n";
                break;
            }
            continue;
        }

        if (command == "p") { // previous move
            if (currentMove == 0 || !replayBoard.undoLastMove()) {std::cout << "Already at replay start.\n";} 
            else {--currentMove;}
            continue;
        }

        if (command == "a") { // autoplay
            while (currentMove < moves.size()) {
                const Checkerboard::ReplayMove& move = moves[currentMove];
                try {
                    replayBoard.play(move.from, move.to, move.turnBlack);
                    ++currentMove;
                }
                catch (const std::exception& e) {
                    std::cout << "Replay stopped on invalid move: " << e.what() << "\n";
                    break;
                }

                std::cout << replayBoard.toUnicodeString() << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1200));
            }

            // replay ended
            if (currentMove >= moves.size()) {std::cout << "Replay completed.\n";}
            continue;
        }

        std::cout << "Unknown replay command. Use n/p/a/q.\n"; // n=next p=previous a=autoplay q=quit
    }
}

void chessMain() {
    Checkerboard cb;
    cb.initialConditions();

    std::string input; 
    bool turnBlack = false; // white starts

    while (true) {
        std::cout << cb.toUnicodeString() << std::endl;
        std::cout << (turnBlack ? "Black" : "White") // options to chose for x player
                  << " move (D2 D4 | undo | save <file> | replay <file> | quit):\n> ";
        std::getline(std::cin, input);

        if (input == "quit") {break;} // quit => exit the game loop

        if (input.rfind("save ", 0) == 0 && input.size() > 5) { // save <file>
            const std::string filePath = input.substr(5);
            cb.saveToFile(filePath); // call the save function of the checkerboard
            std::cout << "~~~Game saved to: " << filePath << "\n\n";
            continue;
        }

        if (input.rfind("replay ", 0) == 0 && input.size() > 7) { // replay <file>
            const std::string filePath = input.substr(7);
            replaySavedGame(filePath); // call the replay function (defined above)
            continue;
        }

        if (input == "undo") { // undo => call the undo function of the checkerboard
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
        // error handling for the input format 
        if (!(iss >> startStr >> endStr)) {
            std::cout << "Invalid format. Use: `D6 D4`\n";
            continue;
        }

        try { // move => call the play function of the checkerboard
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

    Checkerboard cb;
    cb.initialConditions();

    // cb.play(Position("A2"), Position("A4"), true);
    
    std::cout << cb.toString() << std::endl;
    std::cout << cb.toUnicodeString() << std::endl;

    return 0;
}