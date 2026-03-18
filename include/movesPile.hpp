// ==============================================================================
// MOVESPILES : 
// ==============================================================================

#pragma once

#include <stack>
#include <iostream>
#include <string>

#include "piece.hpp"

class Piece;

struct MoveRecord {
    bool turnBlack;
    Position from;
    Position to;
    Piece* movedPiece;
    Piece* capturedPiece;

    bool movedPieceWasFirstMove;
    bool wasPromotion;
    Piece* promotionOldPiece;
};

class MovesPile {
    private:
        // ----------------------------------------------------------------------------
        // private attribute
        // ----------------------------------------------------------------------------    
        std::stack<MoveRecord> _history;

    public:
        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------        
        std::string backMove(); 
        bool empty() const;
        std::size_t size() const;
        void clear();
        void push(const MoveRecord& move);
        const MoveRecord& top() const;
        MoveRecord pop();
        bool canUndo() const;
        bool undoLastMove(Plateau& board);     
};