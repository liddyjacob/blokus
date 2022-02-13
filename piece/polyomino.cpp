#include "polyomino.hpp"
//functions for checking baseform equality
BaseForm rotateClockWise(const BaseForm& bf, const int& rot){
    return bf;
}

BaseForm translateToOrigin(const BaseForm& bf){
    return bf;
}

FreePolyomino::FreePolyomino(BaseForm bf): bf_(bf) {}

bool FreePolyomino::operator==(const FreePolyomino& pr){
    // Check every possible rotation for equivalence of 
    // this free FreePolyomino
    for(int i = 0; i < 4; ++i){
        if (bf_ == translateToOrigin(rotateClockWise(pr.bf_, i))){
            return true;
        }
    }
    return false;
}
