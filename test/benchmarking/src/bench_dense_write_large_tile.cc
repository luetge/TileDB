/**
 * @file   bench_dense_write_large_tile.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2018 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Benchmarks compressed dense 2D write performance with "large" tiles.
 */

#include <chrono>
#include <thread>
#include <tiledb/tiledb>

#include "benchmark.h"

using namespace tiledb;

class Benchmark : public BenchmarkBase {
 protected:
  virtual void setup() {
    ArraySchema schema(ctx_, TILEDB_DENSE);
    Domain domain(ctx_);
    domain.add_dimension(Dimension::create<int32_t>(ctx_, "d1", {{1, 7000}}));
    domain.add_dimension(Dimension::create<int32_t>(ctx_, "d2", {{1, 7000}}));
    schema.set_domain(domain);
    schema.add_attribute(Attribute::create<std::vector<int32_t>>(
        ctx_, "a", {TILEDB_BLOSC_LZ4, 5}));
    Array::create(array_uri_, schema);
  }

  virtual void teardown() {
    VFS vfs(ctx_);
    if (vfs.is_dir(array_uri_))
      vfs.remove_dir(array_uri_);
  }

  virtual void run() {
  }

 private:
  const std::string array_uri_ = "bench_array";

  Context ctx_;
};

int main(int argc, char** argv) {
  Benchmark bench;
  return bench.main(argc, argv);
}