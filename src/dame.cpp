#include "dame.hpp"

#include <cmath>

Dame::Dame(bool isBlack):Piece(isBlack, "dame") {}

bool Dame::isValidMove(const Position &start_pos, const Position &end_pos, bool isCapture, Plateau* board) const {
	const int dx = end_pos.getX() - start_pos.getX();
	const int dy = end_pos.getY() - start_pos.getY();
	const int absDx = std::abs(dx);
	const int absDy = std::abs(dy);

	// end_pos empty.
	if (board->getPiece(end_pos) != nullptr) {
		return false;
	}

	// One-step diagonal move in any direction.
	if (absDx == 1 && absDy == 1) {
		return true;
	}

	// Capture jump: exactly two diagonal squares over an opponent piece.
	if (absDx == 2 && absDy == 2) {
		const Position middle(start_pos.getX() + dx / 2, start_pos.getY() + dy / 2);
		const Piece* middlePiece = board->getPiece(middle);
		return middlePiece != nullptr && middlePiece->getIsBlack() != getIsBlack();
	}

	return false;
}