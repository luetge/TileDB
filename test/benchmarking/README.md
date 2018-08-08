# TileDB benchmarking

This directory contains a simple benchmarking program intended for quick apples-apples performance measurement of common TileDB operations.

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