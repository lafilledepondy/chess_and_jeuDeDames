#pragma once

#include <iostream>
#include <string>

#include "plateau.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "cavalier.hpp"
#include "queen.hpp"
#include "bishop.hpp"
#include "king.hpp"

class Checkerboard: public Plateau {
    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Checkerboard();

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        void initialConditions();
        std::string toString() const;
        std::string toUnicodeString() const;
};