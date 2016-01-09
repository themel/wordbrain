#include <vector>

#include "gtest/gtest.h"
#include "search.h"

struct State {
	int state;
	int left;
	int depth;
};

TEST(Search, Functional) {
	State starting = { 1, 3, 0};
	auto cost = [](const State& state) { return state.depth; };
	auto successors = [](const State& state) { 
		std::vector<State> res;
		res.push_back({state.state + 1, state.left - 1, state.depth + 1});
		return res;
	};
	auto done = [](const State& state) {
		return state.left == 0;
	};


	auto found = Search(starting, successors, done, cost);

	EXPECT_EQ(4, found.state);
	EXPECT_EQ(0, found.left);
	EXPECT_EQ(3, found.depth);
}

