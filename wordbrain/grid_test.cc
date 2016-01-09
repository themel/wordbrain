#include "grid.h"

#include <string>

#include "gtest/gtest.h"

TEST(Wordbrain, Init) {
	Grid one("FOOBARBAZ");
	EXPECT_EQ(" F  O  O \n B  A  R \n B  A  Z \n", one.ToString());
	Grid two("FOODBARDBARBQARG");
	EXPECT_EQ(" F  O  O  D \n B  A  R  D \n B  A  R  B \n Q  A  R  G \n", two.ToString());
}

TEST(Wordbrain, Mask) {
	Grid one("FOOBARBAZ");
	one.Mark({1,1});
	EXPECT_EQ(" F  O  O \n B [A] R \n B  A  Z \n", one.ToString());
}

TEST(Wordbrain, Neighbors) {
	// TODO: More tests.
	Grid grid("FOOBARBAZ");
	std::map<Point, char> one = {
		{{0,1}, 'B'},
		{{1,0}, 'O'},
		{{1,1}, 'A'}
	};
	EXPECT_EQ(one, grid.Neighbors({0,0}));
}

TEST(Wordbrain, MaskedNeighbors) {
	Grid grid("FOOBARBAZ");
	grid.Mark({1,1});
	std::map<Point, char> one = {
		{{0,1}, 'B'},
		{{1,0}, 'O'}
	};
	EXPECT_EQ(one, grid.Neighbors({0,0}));
}

TEST(Wordbrain, Drop) {
	Grid one("FOOBARBAZ");
	one.Mark({2,2});
	one.DropMarked();
	EXPECT_EQ(" F  O  _ \n B  A  O \n B  A  R \n", one.ToString());

	Grid two("FOOBARBAZ");
	two.Mark({0,0});
	two.DropMarked();
	EXPECT_EQ(" _  O  O \n B  A  R \n B  A  Z \n", two.ToString());

	Grid three("FOOBARBAZ");
	three.Mark({0,0});
	three.Mark({0,1});
	three.Mark({0,2});
	three.DropMarked();
	EXPECT_EQ(" _  O  O \n _  A  R \n _  A  Z \n", three.ToString());

	Grid four("FOOBARBAZ");
	four.Mark({0,0});
	four.Mark({1,1});
	four.Mark({2,2});
	four.DropMarked();
	EXPECT_EQ(" _  _  _ \n B  O  O \n B  A  R \n", four.ToString());
}

