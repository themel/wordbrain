#include "dict.h"

#include <string>
#include <sstream>

#include "gtest/gtest.h"


TEST(Dict, Empty) {
	std::stringstream in("");
	Trie dict = ReadDict(in, {});
	EXPECT_EQ(0, dict.Size());
}

TEST(Dict, Words) {
	std::stringstream in("HORSE\nHOBBIT\n");
	Trie dict = ReadDict(in, {});
	EXPECT_EQ(2, dict.Size());
	EXPECT_TRUE(Contains(dict, "HORSE"));
	EXPECT_TRUE(Contains(dict, "HOBBIT"));
}

TEST(Dict, Uppercases) {
	std::stringstream in("horse\nhobbit\n");
	Trie dict = ReadDict(in, {});
	EXPECT_EQ(2, dict.Size());
	EXPECT_TRUE(Contains(dict, "HORSE"));
	EXPECT_TRUE(Contains(dict, "HOBBIT"));
}

TEST(Dict, Filters) {
	std::stringstream in("HORSE\nHÖBBIT\n");
	Trie dict = ReadDict(in, {});
	EXPECT_EQ(1, dict.Size());
	EXPECT_TRUE(Contains(dict, "HORSE"));
}

TEST(Dict, Blacklist) {
	std::stringstream in("HORSE\nHÖBBIT\n");
	Trie dict = ReadDict(in, {"HORSE"});
	EXPECT_EQ(0, dict.Size());
}
