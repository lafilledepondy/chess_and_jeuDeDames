#include <gtest/gtest.h>

#include "exception.hpp"
#include "checkerboard.hpp"

Checkerboard setupKingBoard() {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("E2"), Position("E3"), true);   // white pawn
    cb.play(Position("D7"), Position("D6"), false);  // black pawn 

    return cb;
}

TEST(KingTest, ValidOneSquareMoves) {
    Checkerboard cb = setupKingBoard();

    EXPECT_NO_THROW(cb.play(Position("E1"), Position("E2"), true));
}

TEST(KingTest, MoveTooFarThrows) {
    Checkerboard cb = setupKingBoard();

    EXPECT_THROW(
        cb.play(Position("E1"), Position("E3"), true),
        InvalidMoveException
    );
}

TEST(KingTest, CannotMoveOntoOwnPiece) {
    Checkerboard cb;
    cb.initialConditions();

    EXPECT_THROW(
        cb.play(Position("E1"), Position("D1"), true), // queen is there
        InvalidMoveException
    );
}

TEST(KingTest, CaptureEnemy) {
    Checkerboard cb = setupKingBoard();

    cb.play(Position("C2"), Position("C4"), true);   
    cb.play(Position("C4"), Position("C5"), true);   
    cb.play(Position("C5"), Position("C6"), true);   
    cb.play(Position("E8"), Position("D7"), false);

    EXPECT_NO_THROW(
        cb.play(Position("D7"), Position("C6"), false);
    );
}

TEST(KingTest, SamePositionThrows) {
    Checkerboard cb = setupKingBoard();

    EXPECT_THROW(
        cb.play(Position("E1"), Position("E1"), true),
        InvalidMoveException
    );
}