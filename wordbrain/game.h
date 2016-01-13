#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include <vector>

#include "trie.h"
#include "grid.h"

std::vector<std::string> Solve(std::string input, std::vector<int> lengths, 
                               const Trie* dictionary);

#endif  // defined GAME_H_INCLUDED
