#pragma once

#include <set>
#include <vector>
#include "../piece/polyomino.hpp"


/* 
This function generates each set of polyominoes on 1 to N edges

useful for NxN Blokus.

For example, we expect this function to return the following when 
generate_polyominos_0_to_n(4) is called:

----
x
----
xx
----
xxx 
----
x
xx
----
xxxx
----
xxx
x
----
xxx
 x
----
 xx
xx
----
xx
xx
----
*/
std::unordered_set<FreePolyomino> generate_polyominos_0_to_n(const int& n, bool holes=false);