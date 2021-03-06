#include "polyomino.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

// We need to reflect the baseform to see which is smaller. 
BaseForm reflect(const BaseForm& original){
    BaseForm flipped;

    for (auto i = original.cbegin(); i != original.cend(); ++i)
        flipped.insert(Cell(i->second, i->first));

    return flipped;
}

std::vector<EdgeDir> describeByEdges(const BaseForm& bf){
// get any cell in the set
    std::vector<EdgeDir> edgeDesc;

    if (bf.size() == 0){
        return edgeDesc; 
    }

    Cell edge_start = *(bf.cbegin()); 
    // Note this is not an edge, as it does not 
    // exist in the matrix
    
    // find where the first edge is:
    while (bf.count(edge_start)){
        edge_start.first +=1;
    }

    // Now we have the first edge, we need to keep this coordinate for when we
    // finish looping around the polyomino
    
    Cell current_edge = edge_start;
    
    // need to keep track of the current edge that we are on.

    enum class Direction { UP, RIGHT, DOWN, LEFT };
    // This map is for utility purposes. If we are going up, then 
    //
    // However, if we are on the left side of a block, headed down,
    // then we need to check for something below
    std::unordered_map<Direction, std::pair<int,int>> CCW_blockdiff = 
    {
        {Direction::UP, std::make_pair(0,1)},
        {Direction::RIGHT, std::make_pair(1,0)},
        {Direction::DOWN, std::make_pair(0,-1)},
        {Direction::LEFT, std::make_pair(-1,0)},
    };

    std::unordered_map<Direction, std::pair<int,int>> STR_blockdiff = 
    {
        {Direction::UP, std::make_pair(-1,1)},
        {Direction::RIGHT, std::make_pair(1,1)},
        {Direction::DOWN, std::make_pair(1,-1)},
        {Direction::LEFT, std::make_pair(-1,-1)},
    };

    std::unordered_map<Direction, std::pair<int,int>> CW_blockdiff = 
    {
        {Direction::UP, std::make_pair(-1,1)},
        {Direction::RIGHT, std::make_pair(1,1)},
        {Direction::DOWN, std::make_pair(1,-1)},
        {Direction::LEFT, std::make_pair(-1,-1)},
    };

    std::unordered_map<Direction, Direction> NextDir = 
    {
        {Direction::UP, Direction::LEFT},
        {Direction::RIGHT, Direction::UP},
        {Direction::DOWN, Direction::RIGHT},
        {Direction::LEFT, Direction::DOWN},
    };

    std::unordered_map<Direction, Direction> PrevDir = 
    {
        {Direction::UP, Direction::RIGHT},
        {Direction::RIGHT, Direction::DOWN},
        {Direction::DOWN,Direction::LEFT},
        {Direction::LEFT, Direction::UP},
    };

    Direction current_dir = Direction::UP;

    // Note that if you go CCW, you do not move. If you go STRAIGHT, you move in the 
    // CCW block direction. If you go CW. you move into the STRAIGHT position.
    // Loop around the entire polymino
    do {
        // Check if next turn is right:
        Cell ccw_blocker = current_edge;
        auto ccw_diff = CCW_blockdiff[current_dir];
            ccw_blocker.first += ccw_diff.first; 
            ccw_blocker.second += ccw_diff.second; 

        if (bf.count(ccw_blocker) > 0){
            current_dir = PrevDir[current_dir];
            edgeDesc.push_back(EdgeDir::CCW);

            continue;
        }

        // Check if next turn is straight:
        Cell straight_blocker = current_edge;
        auto straight_diff = STR_blockdiff[current_dir];
            straight_blocker.first += straight_diff.first; 
            straight_blocker.second += straight_diff.second; 

  

        if (bf.count(straight_blocker)  > 0){
            current_edge = ccw_blocker; // move to what would have blocked the right.
            edgeDesc.push_back(EdgeDir::STR);

            continue;
        }
 
        // If it is nonoe of the others, the turn must be left.
        
        current_dir = NextDir[current_dir];
        current_edge = straight_blocker; 
        edgeDesc.push_back(EdgeDir::CW);


    } while ((current_edge != edge_start) || (current_dir != Direction::UP));
    /// when these two conditions are satysfied we have looped the entire polyomino
}

bool edgeDescIsLessThan(std::vector<EdgeDir> hash_l, std::vector<EdgeDir> hash_r){
    const size_t stopping_length = std::min(hash_l.size(), hash_r.size());

    // element-wise comparison
    for(int i = 0; i < stopping_length; ++i){
        if (hash_l[i] != hash_r[i]){
            return static_cast<int>(hash_l[i]) < static_cast<int>(hash_r[i]);
        }
    }
    
    // size comparison if same.
    return hash_l.size() < hash_r.size();
}

std::vector<EdgeDir> canonicalizeEdges(std::vector<EdgeDir> non_can){
// First, double the edge hash.
    std::vector<EdgeDir> edge_hash_double = non_can;

    for(int i = 0; i < non_can.size(); ++i){
        edge_hash_double.push_back(non_can[i]);
    }

    std::vector<EdgeDir> best_edgehash = non_can;

    // Now, generate every possible cycled hash, and compare
    for(int i = 1; i < non_can.size(); ++i){
        std::vector<EdgeDir> comp_edgehash;
        comp_edgehash.insert(comp_edgehash.end(), 
            edge_hash_double.begin() + i,
            edge_hash_double.begin() + i + non_can.size());

        if (edgeDescIsLessThan(comp_edgehash, best_edgehash)){
            best_edgehash = comp_edgehash;
        }
    }


    return(best_edgehash);
}


bool is_rotation(const std::string& str1, const std::string& str2)
{
  if(str1.size()!=str2.size())
    return false;

  std::vector<size_t> prefixes(str1.size(), 0);
  for(size_t i=1, j=0; i<str1.size(); i++) {
    while(j>0 && str1[i]!=str1[j])
      j=prefixes[j-1];
    if(str1[i]==str1[j]) j++;
    prefixes[i]=j;
  }

  size_t i=0, j=0;
  for(; i<str2.size(); i++) {
    while(j>0 && str2[i]!=str1[j])
      j=prefixes[j-1];
    if(str2[i]==str1[j]) j++;
  }
  for(i=0; i<str2.size(); i++) {
    if(j>=str1.size()) return true;
    while(j>0 && str2[i]!=str1[j])
      j=prefixes[j-1];
    if(str2[i]==str1[j]) j++;
  }

  return false;
}

FreePolyomino::FreePolyomino(BaseForm bf): bf_(bf) { 
    generateEdgeHash_();
    canonicalize_hash_();
}

FreePolyomino::FreePolyomino(const FreePolyomino& right){
    bf_ = right.bf_;
    edgeHash_ = right.edgeHash_;
}

bool FreePolyomino::operator==(const FreePolyomino& pr) const{
    // All we need to do is compare the hash values.
    return this->edgeHash_ == pr.edgeHash_;
}

std::vector<EdgeDir> FreePolyomino::getEdgeHash() const{
    return this->edgeHash_;
}

BaseForm FreePolyomino::getBaseForm() const{
    return this->bf_;
}

void FreePolyomino::generateEdgeHash_(){
    // Find edge hash
    auto edgeHash_1 = canonicalizeEdges(describeByEdges(bf_));

    // Find flipped edge hash
    auto edgeHash_2 = canonicalizeEdges(describeByEdges(reflect(bf_)));

    // pick one of these to describe the shape
    // for_each(edgeHash_1.begin(), edgeHash_1.end(), [](auto edgeit){ std::cout << static_cast<int>(edgeit);});
    // std::cout << "\n";

    // for_each(edgeHash_2.begin(), edgeHash_2.end(), [](auto edgeit){ std::cout << static_cast<int>(edgeit);});
    // std::cout << "\n";

    edgeHash_ = edgeDescIsLessThan(edgeHash_1, edgeHash_2) ? edgeHash_1 : edgeHash_2;
}



void FreePolyomino::canonicalize_hash_(){
    
}



