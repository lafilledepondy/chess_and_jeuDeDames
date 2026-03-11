#pragma once

#include "position.hpp"
#include "plateau.hpp"

class Plateau;

class Piece {
    private:
        // ----------------------------------------------------------------------------
        // private attribute
        // ----------------------------------------------------------------------------    
        std::string _name;
        bool _isBlack;

    public:
        // ----------------------------------------------------------------------------
        // constructors
        // ----------------------------------------------------------------------------    
        Piece(bool isBlack, std::string name) : 
            _name(name), _isBlack(isBlack) {};

        // ----------------------------------------------------------------------------
        // abstract methods
        // ---------------------------------------------------------------------------- 
        virtual bool isValidMove(const Position &start_pos, const Position &end_pos, const Position &capture_pos, Plateau* plateau) = 0;

        // ----------------------------------------------------------------------------
        // methods
        // ----------------------------------------------------------------------------         
        std::string toString() const;
};