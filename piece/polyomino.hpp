#pragma once
#include <utility>
#include <vector>

/*
Syntax based off: 
https://parallelstripes.wordpress.com/2009/12/20/generating-polyominoes/
*/
using Cell = std::pair<int, int>;
using BaseForm = std::vector<Cell>;


class FreePolyomino{
public:
    FreePolyomino(BaseForm);

    bool operator==(const FreePolyomino&);
    const int size(){return bf_.size();}
private:
    BaseForm bf_;
};