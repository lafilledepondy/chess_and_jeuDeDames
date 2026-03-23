#include "pawn.hpp"

Pawn::Pawn(bool isBlack):Piece(isBlack, "pawn") {}

bool Pawn::isValidMove(const Position &start_pos, const Position &end_pos, 
    // TODO: en passant is it coded?
    bool isCapture, Plateau* board) const {
    // (void)board;

    const int direction = getIsBlack() ? 1 : -1; // black: move down ; white: move up
    const int dx = end_pos.getX() - start_pos.getX();
    const int dy = end_pos.getY() - start_pos.getY();
    const int startRow = getIsBlack() ? 2 : 7;

    if (isCapture) {
        return std::abs(dx) == 1 && dy == direction;
    }
    
    if (dy == direction && dx == 0) { // normal move 
        return true;
    }

    // first move 2 square advance from the starting row
    if (start_pos.getY() == startRow && 
            dy == 2 * direction && firstMove == true) {
        return true;
    }

    return false;
}