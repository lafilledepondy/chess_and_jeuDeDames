#include "horse.hpp"

Horse::Horse(bool isBlack):Piece(isBlack, "horse") {}

bool Horse::isValidMove(const Position &start_pos, const Position &end_pos, bool isCapture, Plateau* board) const {
    // TODO
    return true;
}