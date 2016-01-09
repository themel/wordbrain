#ifndef WORDBRAIN_TRIE_H_INCLUDED
#define WORDBRAIN_TRIE_H_INCLUDED

#include <map>
#include <memory>
#include <set>
#include <string>

class Trie {
    public:
        // Add word.
        // Wow, this one really really needs stringpiece, but we are only dealing with ministrings in this code anyway.
        void Add(const std::string& word);
        // Return a subtrie representing the suffix trie starting with next.
        const Trie* Get(char next) const;
        // Return the set of possible successor characters.
        std::set<char> Next() const;
        // Return true if this node is an actual word in the trie and not just an internal node.
        bool IsTerminal() const;
        // Returns the number of unique words in the trie. Note: O(N).
        int Size() const;
    private:
        // Are we at a terminal node? This is so that we can know that both SEA and SEAT
        // are a word, but STEA is not while STEAM is.
        bool terminal_ = false;
        typedef std::map<char, std::unique_ptr<Trie>> Successors;
        Successors successors_;
};

bool Contains(const Trie& trie, const std::string& word);

#endif  // defined WORDBRAIN_TRIE_H_INCLUDED
