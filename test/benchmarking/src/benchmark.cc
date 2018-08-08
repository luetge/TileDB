/**
 * @file   benchmark.cc
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
 * Defines common code for the benchmark programs.
 */

#include <string>

#include "benchmark.h"

int BenchmarkBase::main(int argc, char** argv) {
  if (argc < 2)
    return 1;

  std::string task(argv[1]);
  if (task == "setup") {
    setup_base();
  } else if (task == "run") {
    run_base();
  } else if (task == "teardown") {
    teardown_base();
  }

  return 0;
}

void BenchmarkBase::teardown_base() {
  teardown();
}

void BenchmarkBase::setup_base() {
  setup();
}

void BenchmarkBase::run_base() {
  run();
}

void BenchmarkBase::teardown() {
}

void BenchmarkBase::setup() {
}

void BenchmarkBase::run() {
}