#include "bishop.hpp"

Bishop::Bishop(bool isBlack):Piece(isBlack, "bishop") {}

bool Bishop::isValidMove(const Position &start_pos, const Position &end_pos, bool isCapture, Plateau* board) const {
    // TODO
    return true;
}