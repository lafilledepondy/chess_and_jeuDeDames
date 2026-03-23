#include <gtest/gtest.h>

#include "exception.hpp"
#include "plateau.hpp"
#include "rook.hpp"
#include "pawn.hpp"

class RookTestBoard : public Plateau {
public:
    RookTestBoard() : Plateau(8, 8) {}

    void initialConditions() override {}

    void place(Piece* piece, const Position& pos) {
        addPiece(piece, pos);
    }
};

TEST(RookTest, VerticalMoveValid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));

    EXPECT_NO_THROW(cb.play(Position("A1"), Position("A6"), true));
    EXPECT_EQ(cb.getPiece(Position("A1")), nullptr);
    EXPECT_NE(cb.getPiece(Position("A6")), nullptr);
}

TEST(RookTest, HorizontalMoveValid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));

    EXPECT_NO_THROW(cb.play(Position("A1"), Position("F1"), true));
    EXPECT_EQ(cb.getPiece(Position("A1")), nullptr);
    EXPECT_NE(cb.getPiece(Position("F1")), nullptr);
}

TEST(RookTest, DiagonalMoveInvalid) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));

    EXPECT_THROW(cb.play(Position("A1"), Position("B2"), true), InvalidMoveException);
}

TEST(RookTest, CannotJumpOverPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));
    cb.place(new Pawn(true), Position("A3"));

    EXPECT_THROW(cb.play(Position("A1"), Position("A6"), true), InvalidMoveException);
}

TEST(RookTest, CaptureEnemyPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));
    cb.place(new Pawn(false), Position("A6"));

    EXPECT_NO_THROW(cb.play(Position("A1"), Position("A6"), true));
    EXPECT_EQ(cb.getPiece(Position("A1")), nullptr);
    ASSERT_NE(cb.getPiece(Position("A6")), nullptr);
    EXPECT_TRUE(cb.getPiece(Position("A6"))->getIsBlack());
}

TEST(RookTest, CannotCaptureOwnPiece) {
    RookTestBoard cb;
    cb.place(new Rook(true), Position("A1"));
    cb.place(new Pawn(true), Position("A6"));

    EXPECT_THROW(cb.play(Position("A1"), Position("A6"), true), InvalidMoveException);
}