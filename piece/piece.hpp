
#include "color.hpp"
#include "form.hpp"

class Piece{
public:
    Piece(Form, Color);

private:
    Form form_;
    Color c_;
}