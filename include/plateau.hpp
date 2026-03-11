#pragma once

#include <vector>

#include "piece.hpp"

class Piece;

class Plateau {
    protected:
        // ----------------------------------------------------------------------------
        // protected attribute
        // ----------------------------------------------------------------------------    
        std::vector<std::vector<Piece *>> plateau; // <> Piece *[][] Plateau

        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Plateau(int height, int width);

    public:

        // ----------------------------------------------------------------------------
        // getters
        // ---------------------------------------------------------------------------- 
        int getHeight();
        int getWidth();

        // ----------------------------------------------------------------------------
        // abstract methods
        // ---------------------------------------------------------------------------- 
        virtual void initialesConditions() = 0;

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        bool isInside(const Position &pos);
        Piece * getPiece(const Position &pos);
        void turn(const Position &start_pos, const Position &end_pos, bool turnBlack);

    protected : 
        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        void add(Piece * pi, const Position &pos);
        void move(const Position &start_pos, const Position &end_pos);        
};