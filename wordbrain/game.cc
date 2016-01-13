#include "game.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "grid.h"
#include "search.h"
#include "trie.h"

namespace {

struct GameState {
    std::vector<std::string> found;
    // Lengths of characters we're missing, in reverse order.
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

bool Done(const GameState& state) {
        std::cerr << state;
        return state.wanted.empty();
}

int Cost(const GameState& state) {
        // DFS.
        return -state.depth;
}

void Filter(std::map<Point, char>& candidates, std::set<char> allowed_chars) {
        for(std::map<Point, char>::iterator it = candidates.begin(); it != candidates.end();) {
                if(!allowed_chars.count(it->second)) 
                        it = candidates.erase(it);
                else 
                        it++;
        }
}

std::vector<GameState> GetSuccessors(const GameState& state) {
        std::vector<GameState> res;
        // Are we done? No successors.
        if(Done(state)) return res;
        
        std::set<char> possible_chars = state.dict->Next();

        std::map<Point, char> candidates;
        bool in_word = state.position != kInvalidPoint;

        // if we're in a word
        if(in_word) {
                //  just try neighbors of the existing position.
                candidates = state.grid.Neighbors(state.position);
        } else {
                // Else try to start from all available starting positions.
                candidates = state.grid.All();
        }


	int geo_candidates = candidates.size();
        // just consider those where we have words in the dictionary.
        Filter(candidates, possible_chars);

        // preconditions: state.wanted is not empty
        for(const auto& pair : candidates) {
                GameState next = state;
                ++next.depth;
                // Consume the next char.
                next.grid.Mark(pair.first);
                // Navigate down in trie.
                next.dict = next.dict->Get(pair.second);
                // If we're just starting a word, add it.
                if(!in_word) next.found.push_back(std::string());
                // Append to the last word.
                next.found.back().push_back(pair.second);

                // We are now looking for one less character.
                --next.wanted.back();
                // Do we expect a word ending here?
                if(next.wanted.back() == 0) {
                        // Are we at the end of a dictionary word too? 
                        // If not this is a dead end, so let's skip this branch.
                        if(!next.dict->IsTerminal()) continue;

                        // We filled a word!
                        next.wanted.pop_back();
                        // Collapse board.
                        next.grid.DropMarked();
                        // Drop position.
                        next.position = kInvalidPoint;
                        // And start the trie anew.
                        next.dict = next.root;
                } else {
                        // Update position.
                        next.position = pair.first;
                }

                // We should have a valid next state.
                res.push_back(std::move(next));
        }
	std::cerr << res.size() << "/" << geo_candidates << " candidates post filtering.\n";
        return res;
}

}  // namespace

std::vector<std::string> Solve(std::string chars, std::vector<int> lengths, const Trie* dict) {
    // Reverse, lenghts needs to be a stack.
    std::reverse(lengths.begin(), lengths.end());
    GameState initial({{}, std::move(lengths), dict, dict, {std::move(chars)}, kInvalidPoint, 0});
    GameState result = Search(initial, &GetSuccessors, &Done, &Cost);
    return std::move(result.found);
}
