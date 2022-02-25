#include "polyomino.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
//functions for checking baseform equality


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



FreePolyomino::FreePolyomino(BaseForm bf): bf_(bf) { generateEdgeHash(); }

bool FreePolyomino::operator==(const FreePolyomino& pr){
    // All we need to do is compare the hash values.
    return false;
}

void FreePolyomino::generateEdgeHash(){
    // Initialize to empty.
    edgeHash_ = std::vector<FreePolyomino::EdgeDir>();

    std::cout << "Generating stuff\n";

    if (this->size() == 0){
        return;
    }

    // get any cell in the set
    Cell edge_start = *(bf_.begin()); 
    // Note this is not an edge, as it does not 
    // exist in the matrix
    
    // find where the first edge is:
    while (bf_.count(edge_start)){
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
        std::cout << static_cast<int>(current_dir) << "\n";
        std::cout << current_edge.first << " " << current_edge.second << "\n";


        // Check if next turn is right:
        Cell ccw_blocker = current_edge;
        auto ccw_diff = CCW_blockdiff[current_dir];
            ccw_blocker.first += ccw_diff.first; 
            ccw_blocker.second += ccw_diff.second; 

        std::cout << "CCW blocker\n";
        std::cout << ccw_blocker.first << " " << ccw_blocker.second << "\n";


        if (bf_.count(ccw_blocker) > 0){
            current_dir = PrevDir[current_dir];
            edgeHash_.push_back(EdgeDir::CCW);

            continue;
        }

        // Check if next turn is straight:
        Cell straight_blocker = current_edge;
        auto straight_diff = STR_blockdiff[current_dir];
            straight_blocker.first += straight_diff.first; 
            straight_blocker.second += straight_diff.second; 

  

        if (bf_.count(straight_blocker)  > 0){
            current_edge = ccw_blocker; // move to what would have blocked the right.
            edgeHash_.push_back(EdgeDir::STR);

            continue;
        }
 
        // If it is nonoe of the others, the turn must be left.
        
        current_dir = NextDir[current_dir];
        current_edge = straight_blocker; 
        edgeHash_.push_back(EdgeDir::CW);


    } while (current_edge != edge_start && current_dir != Direction::UP);
    /// when these two conditions are satysfied we have looped the entire polyomino

    std::for_each(edgeHash_.begin(), edgeHash_.end(),
        [](auto a){std::cout << static_cast<int>(a) << ", "; });
    std::cout << std::endl;

}