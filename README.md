# A WordBrain Solver.

## Building

Requires [bazel](http://bazel.io).

```
bazel build -c opt wordbrain
bazel test wordbrain:all
```

## Usage

```
bazel-bin/wordbrain/wordbrain --input=RNSOETRTBMIVTWIA \
	--lengths="6 2 3 5" \
	--dictionary=/usr/share/dict/words \
	--blacklist="av mb va rn"
```

## TODO

- Split dictionary trie by length for efficiency.
- Read blacklist from file.
- Allow finding all solutions instead of stopping at first.
