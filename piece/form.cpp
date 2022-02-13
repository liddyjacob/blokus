#include "form.hpp"
//functions for checking baseform equality
BaseForm rotateClockWise(const BaseForm& bf, const int& rot){
    return bf;
}

BaseForm translateToOrigin(const BaseForm& bf){
    return bf;
}

Form::Form(BaseForm bf): bf_(bf) {}

bool Form::operator==(const BaseForm&){
    return false;
}
