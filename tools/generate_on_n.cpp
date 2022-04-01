#include "../utils/polyominoGenerator.hpp"
#include "../piece/polyomino.hpp"
#include <algorithm>
#include <iostream>

int main(){
    auto res = generate_polyominos_0_to_n(8);

    std::for_each(res.begin(), res.end(), [](const FreePolyomino& fp){
        std::cout << fp.getBaseForm() << '\n';});
}