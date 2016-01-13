#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "dict.h"
#include "game.h"
#include "trie.h"

#include "gflags/gflags.h"

using std::string;

DEFINE_string(dictionary, "dict", "Path to dictionary file (one word per line).");
DEFINE_string(input, "", "input grid in row order (CANCATHAT for\ncan\ncat\nhat)");
DEFINE_string(lengths, "", R"(whitespace separated list of expected word lengths, e.g. "3 3 3".)");
DEFINE_string(blacklist, "", R"(whitespace separated list of words to ignore)");

namespace {

template<class T> std::vector<T> SplitSet(const std::string& words) {
        std::vector<T> res;
        std::stringstream strm(words);
        string word;
        while(std::getline(strm, word, ' ')) {
                std::stringstream wordstream(word);
                T val;
                wordstream >> val;
                res.push_back(val);
        }
        return res;
}

// TODO: Split dictionary by length for greater efficiency.
Trie LoadDictionary() {
    std::ifstream in(FLAGS_dictionary);
    std::transform(FLAGS_blacklist.begin(), FLAGS_blacklist.end(), 
                   FLAGS_blacklist.begin(), ::toupper);
    std::vector<std::string> blacklist = SplitSet<string>(FLAGS_blacklist);
    std::cerr << "Blacklist size: " << blacklist.size() << "\n";
    return ReadDict(in, {blacklist.begin(), blacklist.end()});
}

}  // namespace

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  Trie trie = LoadDictionary();
  std::cerr << "Read dictionary, " << trie.Size() << " entries.\n";

  for(const std::string& word : Solve(FLAGS_input, SplitSet<int>(FLAGS_lengths), &trie)) {
	  std::cout << word << "\n";
  }
}
