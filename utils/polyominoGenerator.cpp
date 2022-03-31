#include "polyominoGenerator.hpp"
#include <algorithm> // for_each
#include <iostream>
/*
std::unordered_set<FreePolyomino> generate_polyominos_n_plus_1
  (const std::unordered_set<FreePolyomino> prev_set)
{
    for(const FreePolyomino& fp : prev_set)
}
*/

// ignore any polyominoes with a hole.
bool has_hole(const BaseForm& bf){

    return false;
}

std::unordered_set<FreePolyomino> extend_baseforms_by_one(FreePolyomino pbase){

    // start with the base form
    BaseForm base = pbase.getBaseForm();

    // use this to store the extensions:
    std::unordered_set<FreePolyomino> extensions;
    
    // loop through the baseform, and add a 
    for (Cell c: base){
        // Need to add to a new structure
        // we do not want to overwrite the original
        
        for (int i = -1; i <=1; i+=2){
            BaseForm extendedl = base;
            extendedl.insert(Cell(c.first + i, c.second));

            BaseForm extendedt = base;
            extendedt.insert(Cell(c.first, c.second + i));

            if (!has_hole(extendedl))
                extensions.insert(FreePolyomino(extendedl));

            if (!has_hole(extendedt))
                extensions.insert(FreePolyomino(extendedt));

        }

    }

    return extensions;
}



std::unordered_set<FreePolyomino> generate_polyominos_0_to_n(const int& n){
    // if there are no polyominos to generate...
    if (n < 1)
        return std::unordered_set<FreePolyomino>();

    // Every polyominoes are built off of this base polyomino
    FreePolyomino f1 = FreePolyomino(BaseForm({Cell(0,0)}));

    std::unordered_set<FreePolyomino> all_polyominos = {f1};
    std::unordered_set<FreePolyomino> current_polyominos = {f1};
    
    // Every polyomino is a recursive addition to a previous polyomino
    for (int i = 2; i <= n; ++i){
        std::unordered_set<FreePolyomino> next_polyominos;

        // Loop over existing polyominoes:
        std::for_each(current_polyominos.begin(), current_polyominos.end(),
            [&next_polyominos](FreePolyomino current)
            {
                next_polyominos.merge(extend_baseforms_by_one(current));
            }
        );
        //std::cout << next_polyominos.size() << std::endl;
        current_polyominos = next_polyominos;
        all_polyominos.merge(next_polyominos);

        //std::cout << all_polyominos.size() << std::endl;

    }

    return all_polyominos;
}

