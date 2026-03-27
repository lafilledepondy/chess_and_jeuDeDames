#include <gtest/gtest.h>

#include "exception.hpp"
#include "checkerboard.hpp"

Checkerboard setupPawnBoard() {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("B7"), Position("B5"), false); // p1
    cb.play(Position("B2"), Position("B3"), true);  // P2
    cb.play(Position("C2"), Position("C4"), true); // P3
    /*
          A  B  C  D  E  F  G  H
        1 Ro Ho Bi Qu Ki Bi Ho Ro
        2 Pa  .  .  Pa Pa Pa Pa Pa
        3  .  P2 .  .  .  .  .  .
        4  .  .  P3 .  .  .  .  .
        5  .  p1 .  .  .  .  .  .
        6  .  .  .  .  .  .  .  .
        7 pa  . pa pa pa pa pa pa
        8 ro ho bi qu ki bi ho ro
    */   
    return cb;
}
 
TEST(PawnTest, DoubleStepAfterMoveThrows) {
    Checkerboard cb = setupPawnBoard();

    EXPECT_THROW(
        cb.play(Position("B5"), Position("B3"), false),
        InvalidMoveException
    );
} 

TEST(PawnTest, ValidForwardMove) {
    Checkerboard cb = setupPawnBoard();

    EXPECT_NO_THROW(
        cb.play(Position("B3"), Position("B4"), true)
    );
}

TEST(PawnTest, PiecesMovedCorrectly) {
    Checkerboard cb = setupPawnBoard();

    EXPECT_EQ(cb.getPiece(Position("B7")), nullptr);
    EXPECT_EQ(cb.getPiece(Position("B2")), nullptr);

    EXPECT_NE(cb.getPiece(Position("B5")), nullptr);
    EXPECT_NE(cb.getPiece(Position("B3")), nullptr);
}

TEST(PawnTest, ValidDiagonalCapture) {
    Checkerboard cb = setupPawnBoard();

    EXPECT_NO_THROW(
        cb.play(Position("B5"), Position("C4"), false)
    );

    EXPECT_EQ(cb.getPiece(Position("B5")), nullptr);
    EXPECT_NE(cb.getPiece(Position("C4")), nullptr);
}

TEST(PawnTest, InvalidDiagonalWithoutCapture) {
    Checkerboard cb;
    cb.initialConditions();

    EXPECT_THROW(
        cb.play(Position("B7"), Position("A6"), false),
        InvalidMoveException
    );
}

TEST(PawnTest, InvalidBackwardMove) {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("B7"), Position("B6"), false);

    EXPECT_THROW(
        cb.play(Position("B6"), Position("B7"), false),
        InvalidMoveException
    );
}

TEST(PawnTest, ForwardBlockedThrows) {
    Checkerboard cb = setupPawnBoard();
    cb.play(Position("B3"), Position("B4"), true);

    EXPECT_THROW(
        cb.play(Position("B5"), Position("B4"), false),
        InvalidMoveException
    );
}

TEST(PawnTest, EnPassantCaptureSucceeds) {
    Checkerboard cb;
    cb.initialConditions();

    cb.play(Position("E7"), Position("E5"), false);
    cb.play(Position("A2"), Position("A3"), true);
    cb.play(Position("E5"), Position("E4"), false);
    cb.play(Position("D2"), Position("D4"), true);

    ASSERT_NO_THROW(cb.play(Position("E4"), Position("D3"), false));

    EXPECT_EQ(cb.getPiece(Position("E4")), nullptr);
    EXPECT_EQ(cb.getPiece(Position("D4")), nullptr);

    Piece* landing = cb.getPiece(Position("D3"));
    ASSERT_NE(landing, nullptr);
    EXPECT_FALSE(landing->getIsBlack());
}