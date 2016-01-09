cc_binary(
    name="wordbrain",
    srcs=["main.cc"],
    linkopts=["-lgflags", "-lm"],
    deps=[":trie", ":dict", ":game", ":grid"],
)

cc_library(
    name = "dict",
    hdrs = ["dict.h"], 
    srcs = ["dict.cc"],
    deps = [ ":trie" ],
)
	
cc_test(
    name = "dict_test",
    srcs = ["dict_test.cc"],
    deps=[":dict", ":trie", "@gtest//:main"],
)

cc_library(
	name="trie",
	hdrs=["trie.h"],
	srcs=["trie.cc"],
)

cc_test(
    name = "trie_test",
    srcs = ["trie_test.cc"],
    deps=[":trie", "@gtest//:main"],
)

cc_library(
    name="search",
    hdrs =["search.h"]
)

cc_test(
    name = "search_test",
    srcs = ["search_test.cc"],
    deps=[":search", "@gtest//:main"],
)

cc_library(
    name = "grid",
    hdrs = ["grid.h"],
    srcs = ["grid.cc"],
)

cc_test(
     name = "grid_test",
     srcs = ["grid_test.cc"],
     deps = [":grid", "@gtest//:main"],
)

cc_library(
        name = "game",
        srcs = ["game.cc"],
        hdrs = ["game.h"],
        deps = [":trie", ":search", ":grid"],
)

cc_test(
        name = "game_test",
        srcs = ["game_test.cc"],
        deps = [":game", "dict", "@gtest//:main"],
)
