#include "game.h"

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "grid.h"
#include "search.h"
#include "trie.h"

namespace {

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

	std::cerr << res.size() << "/" << candidates.size() << " successors for\n" << state;
	return res;
}

}  // namespace

Game::Game(std::string chars, std::vector<int> lengths, const Trie* dict) 
: initial_({{}, std::move(lengths), dict, dict, {std::move(chars)}, kInvalidPoint, 0}) { }

GameState Game::Solve() {
	return Search(initial_, &GetSuccessors, &Done, &Cost);
}
