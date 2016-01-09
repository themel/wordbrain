#ifndef WORDBRAIN_DICT_H_INCLUDED
#define WORDBRAIN_DICT_H_INCLUDED

#include <iostream>
#include <set>
#include <string>

#include "trie.h"

// Reads a dictionary one word per line, storing all acceptable words
// (containing only a-z letters) in a trie and returning it.
//
Trie ReadDict(std::istream& in, const std::set<std::string>& blacklist);

#endif // defined WORDBRAIN_DICT_H_INCLUDED
