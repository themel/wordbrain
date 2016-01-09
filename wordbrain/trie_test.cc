#include <cstddef>

#include "gtest/gtest.h"
#include "trie.h"

TEST(Trie, Empty) {
	Trie empty;
    EXPECT_EQ(0, empty.Size());
	EXPECT_TRUE(empty.Next().empty());
	EXPECT_EQ(nullptr, empty.Get('A'));
	EXPECT_FALSE(Contains(empty, "foo"));
}

TEST(Trie, One) {
	Trie trie;
	trie.Add("one");
    EXPECT_EQ(1, trie.Size());
	EXPECT_TRUE(Contains(trie, "one"));
	EXPECT_FALSE(Contains(trie, "two"));
	EXPECT_FALSE(Contains(trie, "ones"));
	EXPECT_FALSE(Contains(trie, "on"));
	EXPECT_EQ(std::set<char>{'o'}, trie.Next());
	EXPECT_NE(nullptr, trie.Get('o'));
}

TEST(Trie, Two) {
	Trie trie;
	trie.Add("one");
	trie.Add("two");
    EXPECT_EQ(2, trie.Size());
	EXPECT_TRUE(Contains(trie, "one"));
	EXPECT_TRUE(Contains(trie, "two"));
	EXPECT_FALSE(Contains(trie, "three"));
	// parens for the macro!
	EXPECT_EQ(std::set<char>({'o', 't'}), trie.Next());
	EXPECT_NE(nullptr, trie.Get('o'));
	EXPECT_NE(nullptr, trie.Get('t'));
	EXPECT_EQ(nullptr, trie.Get('A'));
}

TEST(Trie, Prefix) {
	Trie trie;
	trie.Add("one");
	trie.Add("on");
    EXPECT_EQ(2, trie.Size());
	EXPECT_TRUE(Contains(trie, "one"));
	EXPECT_TRUE(Contains(trie, "on"));
	EXPECT_FALSE(Contains(trie, "o"));
	EXPECT_FALSE(Contains(trie, "ones"));
	EXPECT_EQ(std::set<char>{'o'}, trie.Next());
}
