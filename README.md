# mulle-inline-cache-lookup

A test project to be used in conjunction with
[Godbolt's Compiler Explorer](https://godbolt.org). Possibly the greatest
project name in existence.

This project has a companion article that explains the background in sufficient
detail along with code commentary any analysis:
[mulle-objc: investigation to inline mulle_objc_object_call](//www.mulle-kybernetik.com/weblog/mulle_objc_inline_skater.html)


## How this works

[`code.cpp`](//github.com/mulle-nat/mulle-inline-cache-lookup/blob/master/code.cpp)
is the start for this project. This file does technically exactly the same thing
that `mulle_objc_object_call` does. Especially all the offsets in the various
`structs` are identical. The code has just been stripped down to the bare
minimum.

`code.cpp` is pasted into [Godbolt's Compiler Explorer](https://godbolt.org)
where various different compiler variations can be tried. Some of the more
interesting outcomes have been saved in the
[results](//github.com/mulle-nat/mulle-inline-cache-lookup/tree/master/results)
folder.

To actually run a benchmark to compare these files, there is a
[test](//github.com/mulle-nat/mulle-inline-cache-lookup/tree/master/test)
folder. You can use
[`run-test.sh`](//github.com/mulle-nat/mulle-inline-cache-lookup/blob/master/test/
run-test.sh)
to benchmark a single result or multiple results.
By default `run-test.sh` will benchmark all `x86_64` files in the
results folder plus the handcoded .s files in the test folder.

If you are on a different architecture, let's say PPC for instance, you could
run a single PPC result file with `./run-test ../results/powerpc-gcc-4.8.txt`.

For each file the tester will print a line like this:

```
clang-3.8(66): 3.30 3.29 3.29
```

The `66` is the number of bytes used by the call. The other three values are
the user value from `time -p` for three runs of the benchmark. These are the
numbers I got running the test on my 3,69 GHz Intel Core i7:

```
clang-3.2(66): 3.36 3.36 3.36
clang-3.5(66): 3.37 3.36 3.36
clang-3.7(66): 3.29 3.29 3.29
clang-3.8(66): 3.30 3.29 3.29
clang-3.9(66): 3.29 3.29 3.29
clang-3.9-Os(63): 3.53 3.53 3.52
gcc-4.7(64): 3.61 3.61 3.61
gcc-7.0(65): 3.35 3.35 3.36
gcc-7.0-Os(65): 3.15 3.15 3.15
icc-17.0(67): 3.35 3.35 3.35
nat-call-1.s(66): 3.14 3.14 3.14
nat-call-2.s(57): 3.08 3.08 3.08
nat-call-3.s(51): 3.09 3.08 3.07
```

Read above-mentioned article for a commentary and interpretation of it all.
