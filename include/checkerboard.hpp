#pragma once

#include <string>

#include "plateau.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "cavalier.hpp"
#include "queen.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "movesPile.hpp"

class Checkerboard: public Plateau {
    private:
        MovesPile _movesHistory;

    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Checkerboard();

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        void initialConditions();
        void play(const Position &start_pos, const Position &end_pos, bool turnBlack);
        bool undoLastMove();
        bool canUndo() const;
        std::string toString() const;
        std::string toUnicodeString() const;
        void loadFromFile(const std::string& filename);
        void saveToFile(const std::string& filename) const;
};