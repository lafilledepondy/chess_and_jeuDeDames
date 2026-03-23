#pragma once

#include "rook.hpp"
#include "bishop.hpp"

class Queen : public Rook, public Bishop {
    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Queen(bool isBlack);

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------        
        bool isValidMove(const Position &start_pos, const Position &end_pos, 
            bool isCapture, Plateau* board) const;
};