#pragma once

#include "piece.hpp"

class Bishop: public virtual Piece {
    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Bishop(bool isBlack);

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------        
        bool isValidMove(const Position &start_pos, const Position &end_pos, 
            bool isCapture, Plateau* board) const;
};