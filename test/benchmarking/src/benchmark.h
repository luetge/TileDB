/**
 * @file   benchmark.h
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
 * Declares common code for the benchmark programs.
 */

#ifndef TILEDB_BENCHMARK_H
#define TILEDB_BENCHMARK_H

#include <cassert>
#include <string>

/**
 * Base class for benchmarks.
 */
class BenchmarkBase {
 public:
  /**
   * Main method of the benchmark, which invokes setup, run, or teardown
   * depending on the arguments given.
   */
  int main(int argc, char** argv);

  /**
   * Pre run setup method.
   */
  void setup_base();

  /** Post run cleanup. */
  void teardown_base();

  /** Run method. */
  void run_base();

 protected:
  virtual void setup();
  virtual void teardown();
  virtual void run();

private:
  void print_json(const std::string& name, uint64_t value);
};

#endif