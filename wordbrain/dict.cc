#include "dict.h"

#include <algorithm>
#include <set>
#include <string>

namespace {

bool Accept(const std::string& str) {
    for(char c : str) 
       if(c < 'A' || c > 'Z') return false;
    return true;
}

}  // namespace

Trie ReadDict(std::istream& in, const std::set<std::string>& blacklist) {
    Trie res;
    std::string line;
    while(std::getline(in, line)) {
        std::transform(line.begin(), line.end(), line.begin(), ::toupper);
        if(Accept(line) && !blacklist.count(line))
            res.Add(line);
    }
    return res;
}

