#pragma once
#include <utility>
#include <vector>

/*
Syntax based off: 
https://parallelstripes.wordpress.com/2009/12/20/generating-polyominoes/
*/
using Cell = std::pair<int, int>;
using BaseForm = std::vector<Cell>;


class Form{
public:
    Form(BaseForm);

    bool operator==(const BaseForm&);
    const int size(){return bf_.size();}
private:
    BaseForm bf_;
};