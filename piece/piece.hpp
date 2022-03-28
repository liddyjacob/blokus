#pragma once

#include "color.hpp"
#include "polyomino.hpp"

class Piece{
public:
    Piece(FreePolyomino, Color);

private:
    FreePolyomino form_;
    Color c_;
}