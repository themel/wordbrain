#include "game.h"

#include <string>
#include <sstream>

#include "dict.h"
#include "gtest/gtest.h"

TEST(Game, Functional) {
    std::stringstream str("cat\nhat\ncan\ncanoe\n");
    Trie dict = ReadDict(str, {});
    Game foo("CATCANHAT", {3,3,3}, &dict);
    GameState final = foo.Solve();
    std::cerr << final;
    EXPECT_EQ(3, final.found.size());
    EXPECT_TRUE(final.wanted.empty());
}

