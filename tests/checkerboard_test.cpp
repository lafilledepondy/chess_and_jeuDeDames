#include <gtest/gtest.h>

#include "checkerboard.hpp"
#include "exception.hpp"

TEST(CheckerboardUndoTest, UndoSimpleMoveRestoresBoard) {
    Checkerboard cb;
    cb.initialConditions();

    ASSERT_TRUE(cb.canUndo() == false);

    cb.play(Position("B7"), Position("B5"), false);

    ASSERT_TRUE(cb.canUndo());
    EXPECT_EQ(cb.getPiece(Position("B7")), nullptr);
    EXPECT_NE(cb.getPiece(Position("B5")), nullptr);

    ASSERT_TRUE(cb.undoLastMove());

    EXPECT_NE(cb.getPiece(Position("B7")), nullptr);
    EXPECT_EQ(cb.getPiece(Position("B5")), nullptr);

    // Pawn should recover firstMove after undo and allow double-step again.
    EXPECT_NO_THROW(cb.play(Position("B7"), Position("B5"), false));
}

TEST(CheckerboardUndoTest, UndoCaptureRestoresCapturedPiece) {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("B7"), Position("B5"), false);
    cb.play(Position("B2"), Position("B3"), true);
    cb.play(Position("C2"), Position("C4"), true);

    Piece* attackerBefore = cb.getPiece(Position("B5"));
    Piece* victimBefore = cb.getPiece(Position("C4"));
    ASSERT_NE(attackerBefore, nullptr);
    ASSERT_NE(victimBefore, nullptr);

    ASSERT_NO_THROW(cb.play(Position("B5"), Position("C4"), false));

    Piece* capturedSquareAfterCapture = cb.getPiece(Position("C4"));
    ASSERT_NE(capturedSquareAfterCapture, nullptr);
    EXPECT_EQ(capturedSquareAfterCapture, attackerBefore);

    ASSERT_TRUE(cb.undoLastMove());

    Piece* restoredAttacker = cb.getPiece(Position("B5"));
    Piece* restoredCaptured = cb.getPiece(Position("C4"));

    ASSERT_NE(restoredAttacker, nullptr);
    ASSERT_NE(restoredCaptured, nullptr);
    EXPECT_EQ(restoredAttacker, attackerBefore);
    EXPECT_EQ(restoredCaptured, victimBefore);
}

TEST(CheckerboardUndoTest, UndoEnPassantRestoresCapturedPawn) {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("E7"), Position("E5"), false);
    cb.play(Position("A2"), Position("A3"), true);
    cb.play(Position("E5"), Position("E4"), false);
    cb.play(Position("D2"), Position("D4"), true);

    Piece* attackerBefore = cb.getPiece(Position("E4"));
    Piece* victimBefore = cb.getPiece(Position("D4"));
    ASSERT_NE(attackerBefore, nullptr);
    ASSERT_NE(victimBefore, nullptr);

    ASSERT_NO_THROW(cb.play(Position("E4"), Position("D3"), false));
    ASSERT_TRUE(cb.undoLastMove());

    EXPECT_EQ(cb.getPiece(Position("E4")), attackerBefore);
    EXPECT_EQ(cb.getPiece(Position("D4")), victimBefore);
    EXPECT_EQ(cb.getPiece(Position("D3")), nullptr);
}
