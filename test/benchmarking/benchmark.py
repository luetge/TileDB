#!/usr/bin/env python

import argparse
import glob
import json
import os
import subprocess
import sys

benchmark_src_dir = os.path.abspath('src')
benchmark_build_dir = os.path.abspath('build')

if os.name == 'posix':
    if sys.platform == 'darwin':
        os_name = 'mac'
        libtiledb_name = 'libtiledb.dylib'
    else:
        os_name = 'linux'
        libtiledb_name = 'libtiledb.so'
elif os.name == 'nt':
    os_name = 'windows'
    libtiledb_name = 'tiledb.dll'


def drop_fs_caches():
    """Drops local filesystem caches."""
    if os_name == 'linux':
        subprocess.call(
            ['sudo', 'sh', '-c', 'echo 3 >/proc/sys/vm/drop_caches'])
    elif os_name == 'mac':
        subprocess.call(['sudo', 'purge'])
    else:
        print('WARNING: FS cache drop unimplemented')


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
        if os.path.exists(os.path.join(libdir, libtiledb_name)):
            return os.path.abspath(d)
    return None


def list_benchmarks(show=False):
    """Returns a list of benchmarks."""
    executables = glob.glob(os.path.join(benchmark_build_dir, 'bench_*'))
    if show:
        print('{} benchmarks:'.format(len(executables)))
    names = []
    for exe in sorted(executables):
        name = os.path.basename(exe)
        names.append(name)
        if show:
            print('  {}'.format(name))
    return names


def build_benchmark(args):
    """Builds all the benchmark programs."""
    if not os.path.exists(benchmark_build_dir):
        os.mkdir(benchmark_build_dir)
    tiledb_path = find_tiledb_path(args)
    subprocess.check_output(
        ['cmake', '-DCMAKE_PREFIX_PATH={}'.format(tiledb_path),
         benchmark_src_dir],
        cwd=benchmark_build_dir)
    subprocess.check_output(['make', '-j4'], cwd=benchmark_build_dir)


def run_benchmark(args):
    """Runs the benchmark programs."""
    benchmarks = list_benchmarks()
    for b in benchmarks:
        exe = os.path.join(benchmark_build_dir, b)
        output_json = subprocess.check_output([exe])
        # results = json.loads(output_json)


def main():
    parser = argparse.ArgumentParser(description='Runs TileDB benchmarks.')
    parser.add_argument('--tiledb', metavar='PATH',
                        default='../../dist',
                        help='Path to TileDB installation directory. You can '
                             'also set the TILEDB_PATH environment variable.')
    parser.add_argument('-l', '--list', action='store_true', default=False,
                        help='List all available benchmarks and exit.')
    args = parser.parse_args()

    if find_tiledb_path(args) is None:
        print('Error: TileDB installation not found in directory \'{}\''.format(
            args.tiledb))
        sys.exit(1)

    build_benchmark(args)

    if args.list:
        list_benchmarks(show=True)
        sys.exit(0)

    run_benchmark(args)


if __name__ == '__main__':
    main()
