#include "trie.h"

#include <utility>

void Trie::Add(const std::string& word) {
    // if we're at the destination, mark terminal.
    if(word.empty()) {
	    terminal_ = true;
	    return;
    }

    auto res = successors_.insert(std::make_pair(word[0], nullptr));

    // if we inserted, we need to alloc a new subtrie
    if(res.second) {
        res.first->second.reset(new Trie);
    }

    // and recurse.
    res.first->second->Add(word.substr(1));
}

const Trie* Trie::Get(char next) const {
    Successors::const_iterator it = successors_.find(next);
    return it == successors_.end() ? nullptr: it->second.get();
}

std::set<char> Trie::Next() const {
    std::set<char> res;
    for(const auto& pair : successors_) {
        res.insert(pair.first);
    }
    return res;
}


bool Trie::IsTerminal() const {
    return terminal_;
}

bool Contains(const Trie& trie, const std::string& word) {
	if(word.empty()) 
		return trie.IsTerminal();

	if(const Trie* next = trie.Get(word[0]))
		return Contains(*next, word.substr(1));
	else
		return false;
}

int Trie::Size() const {
    int this_size = terminal_ ? 1 : 0;
    for(const auto& pair : successors_) 
        this_size += pair.second->Size();
    return this_size;
}
