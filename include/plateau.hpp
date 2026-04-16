#pragma once

#include <vector>

#include "piece.hpp"

class Piece;

class Plateau {
    protected:
        // ----------------------------------------------------------------------------
        // protected attribute
        // ----------------------------------------------------------------------------
        std::vector<std::vector<Piece *>> plateau_vec; // <> Piece *[][] Plateau
        int blackScore;
        int whiteScore;

        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------
        Plateau(int height, int width);

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------
        void addPiece(Piece *pi, const Position &pos);
        void movePiece(const Position &start_pos, const Position &end_pos);
        void addCaptureScore(bool capturerBlack, const Piece* capturedPiece);
        void undoCaptureScore(bool capturerBlack, const Piece* capturedPiece);

    public:
        // ----------------------------------------------------------------------------
        // getters
        // ----------------------------------------------------------------------------
        int getHeight() const;
        int getWidth() const;
        int getScore(bool forBlack) const;
        int getMaterialAdvantage(bool forBlack) const;

        // ----------------------------------------------------------------------------
        // abstract methods
        // ----------------------------------------------------------------------------
        virtual void initialConditions() = 0;

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------
        bool isInside(const Position &pos) const;
        Piece *getPiece(const Position &pos) const;
        virtual bool canEnPassantCapture(const Position &start_pos, const Position &end_pos) const;
        virtual Position getEnPassantCapturedPosition(const Position &start_pos, const Position &end_pos) const;
        void play(const Position &start_pos, const Position &end_pos, bool turnBlack);
};