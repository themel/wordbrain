#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include <vector>

#include "trie.h"
#include "grid.h"

struct GameState {
    std::vector<std::string> found;
    // number of words missing.
    std::vector<int> wanted;
    const Trie* dict;
    const Trie* root; // TODO: UGLY, fix.
    Grid grid;
    Point position;
    int depth;
};

inline std::ostream& operator <<(std::ostream& str, const GameState& state) {
    str << "grid:\n" << state.grid.ToString() << "\n";
    str << "found=[";
    for(const std::string& word: state.found) {
        str << word << " ";
    }
    str << "]\n";
    str << "wanted=[";
    for(int count : state.wanted) {
        str << count << " ";
    }
    str << "]\n";
    str << "position=" << state.position << "\n";
    str << "depth=" << state.depth << "\n";
    return str;
}

// TODO: Probably not a class?
class Game {
    public:
        Game(std::string in, std::vector<int> words, const Trie* dict);
        GameState Solve();
    private:
        GameState initial_;
};

#endif  // defined GAME_H_INCLUDED
