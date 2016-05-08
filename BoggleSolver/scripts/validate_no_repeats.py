import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", help="Path to file to run verify on")
    args = parser.parse_args()

    word_set = set()
    with open(args.f, 'r') as fp:
        lines = fp.readlines()

        print("Evaluating {} lines".format(len(lines)))

        dup_count = 0

        for line in lines:
            if line in word_set:
                print("Found repeated word {}").format(line)
                dup_count += 1
            else:
                word_set.add(line)

        print("Duplicate count {}".format(dup_count))
