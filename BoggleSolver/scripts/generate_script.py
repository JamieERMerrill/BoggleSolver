import argparse
import string
import random

def generateLine(count, lowers):
    letters = []
    for i in range(0, count):
        letters.append(random.choice(lowers))
    return ','.join(letters) + '\n'


if __name__ == '__main__':
    lowers = string.ascii_lowercase
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', type=int, required=True, help="Number of columns")
    parser.add_argument('-r', type=int, required=True, help="Number of rows")
    args = parser.parse_args()

    print("Generating file with {} columns, {} rows".format(args.c, args.r))

    lines = []
    for i in range(0, args.r):
        lines.append(generateLine(args.c, lowers))

    with open("new_puzzle.csv", 'w') as fp:
        fp.writelines(lines)
