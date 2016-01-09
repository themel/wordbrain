A WordBrain solver.

Usage: 

bin/main --input=RNSOETRTBMIVTWIA --lengths="5 3 2 6" --dict=/usr/share/dict/words

TODO:
- Split dictionary trie by length for efficiency.
- Reverse length argument.
- Uppercase blacklist.
- Read blacklist from file.
- Don't always abort when a solution is found.
