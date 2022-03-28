#include "polyominoGenerator.hpp"

/*
std::unordered_set<FreePolyomino> generate_polyominos_n_plus_1
  (const std::unordered_set<FreePolyomino> prev_set)
{
    for(const FreePolyomino& fp : prev_set)
}
*/

std::unordered_set<FreePolyomino> generate_polyominos_0_to_n(const int& n, bool holes){
    // if there are no polyominos to generate...
    if (n < 1)
        return std::unordered_set<FreePolyomino>();


    // Every polyominoes are built off of 
    FreePolyomino f1 = FreePolyomino(BaseForm({Cell(0,0)}));

    std::unordered_set<FreePolyomino> all_polyominos = {f1};
    std::unordered_set<FreePolyomino> current_polyominos = {f1};

    return all_polyominos;
}

