#pragma once
#include <utility>
#include <vector>
#include <unordered_set>
/*
Syntax based off: 
https://parallelstripes.wordpress.com/2009/12/20/generating-polyominoes/
*/
using Cell = std::pair<int, int>;


// Need to define hash for this
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

using BaseForm = std::unordered_set<Cell, pair_hash>;

BaseForm reflect(const BaseForm&);

// When analyzing multiple polyminos, this is helpful.
// STRaight, CounterClockWise, ClockWise.
enum class EdgeDir{STR, CCW, CW};

std::vector<EdgeDir> describeByEdges(const BaseForm&);

std::vector<EdgeDir> canonicalizeEdges(std::vector<EdgeDir>);

/*
A Free Polyomino without holes
https://en.wikipedia.org/wiki/Polyomino

If there is a hole, we will have UNDEFINED BEHAVIOR.

Free polyminos


Generating polyominos:
http://www.csun.edu/~ctoth/Handbook/chap14.pdf

Hashing Polyominos:
https://stackoverflow.com/questions/12010168/algorithm-to-identify-a-unique-free-polyomino-or-polyomino-hash

Compairing circular hashes:
https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation
https://stackoverflow.com/questions/2553522/interview-question-check-if-one-string-is-a-rotation-of-other-string/2555887#2555887

*/
class FreePolyomino{
public:
    // The base form is needed to compute the edge hash.
    FreePolyomino(BaseForm);
    FreePolyomino(const FreePolyomino&);

    bool operator==(const FreePolyomino&) const;
    int size() const{return bf_.size();}

    std::vector<EdgeDir> getEdgeHash() const;
private:

    // This algorithm generates the edgehash and saves it.
    void generateEdgeHash_();
    
    // this algorithm determines what the edges are for the base polyomino.
    void canonicalize_hash_();

    // This base form contains the physical structure of the polymino
    // It is not necessary but will be helpful if we want to add
    // any display to this program
    BaseForm bf_;
    // This variable will allow us to quickly build and 
    // compare polyminos. All we need to do is compare 
    // edge hashes, which are simply circular lists
    // describing the edges
    std::vector<EdgeDir> edgeHash_;
};

namespace std
{
    template <>
    struct hash<FreePolyomino>
    {
        size_t operator()(const FreePolyomino& fp) const{
            std::size_t seed = fp.size();
            for(auto& i : fp.getEdgeHash()) {
              seed ^= static_cast<int>(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }

    };
}