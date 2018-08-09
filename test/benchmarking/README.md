# TileDB benchmarking

This directory contains simple benchmarking programs intended for quick apples-apples performance measurement of common TileDB operations.

## How to run

1. Build TileDB and install locally.

    ```bash
    $ cd TileDB/build
    $ ../bootstrap && make -j4 && make install-tiledb
    $ cd ../dist
    $ export TILEDB_INSTALL=`pwd`
    ```

2. Run the benchmarking script.

    ```bash
    $ cd TileDB/test/benchmarking
    $ ./benchmark.py
    ```
    
The Python script is just a harness for executing the benchmark program, which uses the C++ API.

## Adding benchmarks

1. Create a new file `src/bench_<name>.cc`.
2. Subclass from the `BenchmarkBase` class and implement the desired methods.
3. In the `main` function, call the `BenchmarkBase::main` function of an instance of your subclass.
4. Add `bench_<name>` to the `BENCHMARKS` list in `src/CMakeLists.txt`.

When you next run `benchmark.py` it will build and run the added benchmark.