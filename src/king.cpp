#include "king.hpp"

King::King(bool isBlack):Piece(isBlack, "king") {}

bool King::isValidMove(const Position &start_pos, const Position &end_pos, bool isCapture, Plateau* board) const {
    // TODO: first move with rook

    int dx = abs(end_pos.getX() - start_pos.getX());
    int dy = abs(end_pos.getY() - start_pos.getY());
    Piece* target = board->getPiece(end_pos);

    // no move
    if (dx == 0 && dy == 0) return false;

    // king moves only 1 square
    if (dx > 1 || dy > 1) return false;

    if (isCapture) {
        return target != nullptr && target->getIsBlack() != getIsBlack();
    } else {
        return target == nullptr;
    }
}
