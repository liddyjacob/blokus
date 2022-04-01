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
bool has_hole_n_lt_8(const BaseForm& bf, const Cell& newCell);

// ignore any polyominoes with a hole.
// We only need to check near the new cell
bool has_hole(const BaseForm& bf, const Cell& newCell){
    if (bf.size() <= 8)
        return has_hole_n_lt_8(bf, newCell);

    return true; 
}

    // this algorithm only works up to n = 8
    

bool has_hole_n_lt_8(const BaseForm& bf, const Cell& newCell){
    // These are to check if there is possibly a hole 
    Cell north(newCell.first, newCell.second + 2);
    Cell northWest(newCell.first - 1, newCell.second + 1);
    Cell west(newCell.first - 2, newCell.second);
    Cell southWest(newCell.first - 1, newCell.second - 1);
    Cell south(newCell.first, newCell.second - 2);
    Cell southEast(newCell.first + 1, newCell.second - 1);
    Cell east(newCell.first + 2, newCell.second);
    Cell northEast(newCell.first + 1, newCell.second + 1);

    // These are to check if any potential nearby holes are filled.
    Cell nearNorth(newCell.first, newCell.second + 1);
    Cell nearWest(newCell.first - 1, newCell.second);
    Cell nearSouth(newCell.first, newCell.second - 1);
    Cell nearEast(newCell.first + 1, newCell.second);

    // check every possible hole associated with this new block
    if (bf.count(nearNorth) == 0){

        BaseForm bfNorth = bf;
        BaseForm northHole({northWest, north, northEast});

        bfNorth.merge(northHole);

        if (bfNorth.size() == bf.size()){
            return true;
        }
    } 
    if (bf.count(nearWest) == 0){
        BaseForm bfWest = bf;
        BaseForm westHole({northWest, west, southWest});

        bfWest.merge(westHole);
        if (bfWest.size() == bf.size()){
            return true;
        }
    }
    if (bf.count(nearSouth) == 0){
        BaseForm bfSouth = bf;
        BaseForm southHole({southWest, south, southEast});

        bfSouth.merge(southHole);
        if (bfSouth.size() == bf.size()){
            return true;
        }

    }
    if (bf.count(nearEast) == 0){
        BaseForm bfEast = bf;
        BaseForm eastHole({southEast, east, northEast});

        bfEast.merge(eastHole);
        if (bfEast.size() == bf.size()){
            return true;
        }
    }

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
            // left / right extensions
            BaseForm extendedx = base;
            Cell cx(c.first + i, c.second);
            extendedx.insert(cx);

            // top/bottom
            BaseForm extendedy = base;
            Cell cy(c.first, c.second + i);
            extendedy.insert(cy);

            if (!has_hole(extendedx, cx))
                extensions.insert(FreePolyomino(extendedx));
            

            if (!has_hole(extendedy, cy))
                extensions.insert(FreePolyomino(extendedy));
            

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

