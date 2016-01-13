#include "game.h"

#include <string>
#include <sstream>

#include "dict.h"
#include "gtest/gtest.h"

TEST(Game, Functional) {
    std::stringstream str("cat\nhat\ncan\ncanoe\n");
    Trie dict = ReadDict(str, {});
    std::vector<std::string> expected = {"CAT", "CAN", "HAT"};
    EXPECT_EQ(expected, Solve("CATCANHAT", {3,3,3}, &dict));
}

