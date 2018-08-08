#!/usr/bin/env python

import argparse
import glob
import json
import os
import subprocess
import sys

benchmark_src_dir = os.path.abspath('src')
benchmark_build_dir = os.path.abspath('build')


def find_tiledb_path(args):
    """
    Returns the path to the TileDB installation, or None if it can't be determined.

    :param args: argparse args instance
    :return: path or None
    """
    dirs = [args.tiledb]
    if 'TILEDB_PATH' in os.environ:
        dirs.append(os.environ['TILEDB_PATH'])
    for d in dirs:
        libdir = os.path.join(d, 'lib')
        if os.path.exists(os.path.join(libdir, 'libtiledb.dylib')):
            return os.path.abspath(d)
    return None


def get_all_benchmarks():
    pass



def build_benchmark(args):
    if not os.path.exists(benchmark_build_dir):
        os.mkdir(benchmark_build_dir)
    tiledb_path = find_tiledb_path(args)
    print('Building benchmark program...')
    subprocess.check_output(
        ['cmake', '-DCMAKE_PREFIX_PATH={}'.format(tiledb_path),
         benchmark_src_dir],
        cwd=benchmark_build_dir)
    subprocess.check_output(['make', '-j4'], cwd=benchmark_build_dir)
    print('Done.')


def run_benchmark(args):
    exe = os.path.join(benchmark_build_dir, 'benchmark')
    output_json = subprocess.check_output([exe])
    results = json.loads(output_json)


def main():
    parser = argparse.ArgumentParser(description='Runs TileDB benchmarks.')
    parser.add_argument('--tiledb', metavar='PATH',
                        default='../../dist',
                        help='Path to TileDB installation directory. You can '
                             'also set the TILEDB_PATH environment variable.')
    args = parser.parse_args()

    if find_tiledb_path(args) is None:
        print('Error: TileDB installation not found in directory \'{}\''.format(
            args.tiledb))
        sys.exit(1)

    build_benchmark(args)
    run_benchmark(args)


if __name__ == '__main__':
    main()
