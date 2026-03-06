#!/usr/bin/env python3
from argparse import *
from subprocess import *
import sys

ap = ArgumentParser()
ap.add_argument('program', nargs='+')
ap.add_argument('-x', '--num-to-guess', type=int, dest='x', default=42)
ap.add_argument('-q', '--quiet', dest='quiet', action='store_true')
args = ap.parse_args()

def write(p: Popen[str], line):
    assert p.poll() is None and p.stdin is not None
    if not args.quiet:
        print(f'Write: {line}', flush=True)
    p.stdin.write(f"{line}\n")
    p.stdin.flush()
def read(p: Popen[str]) -> str:
    assert p.poll() is None and p.stdout is not None
    line = p.stdout.readline().strip()
    assert line != ''
    if not args.quiet:
        print(f'Read: {line}', flush=True)
    return line
def wrong(p: Popen[str], msg):
    p.kill()
    print(f"Wrong answer: {msg}")
    Popen("rm -rf tc/input.txt tc/sol1.txt tc/sol2.txt")
    sys.exit(1)

q = 0
with Popen(
    " ".join(args.program), shell=True,
    stdin=PIPE, stdout=PIPE, universal_newlines=True
) as p:
    while True:
        q += 1
        if q > 50:
            wrong(p, "too many queries")
        try:
            s = read(p)
            guess = int(s)
        except:
            wrong(p, f"invalid input: {s}")
        if guess == args.x:
            write(p, '=')
            break
        elif guess > args.x:
            write(p, '>')
        else:
            write(p, '<')
    sys.stdout.write(f"Number of query: {q}\n")
    sys.stdout.flush()

