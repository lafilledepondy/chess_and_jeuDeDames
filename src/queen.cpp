#include "queen.hpp"

Queen::Queen(bool isBlack): Piece(isBlack, "queen"), Rook(isBlack), Bishop(isBlack) {}

bool Queen::isValidMove(const Position &start_pos, const Position &end_pos, bool isCapture, Plateau* board) const {
    // moves like rook or a bishop
    return Rook::isValidMove(start_pos, end_pos, isCapture, board) ||
        Bishop::isValidMove(start_pos, end_pos, isCapture, board);
}