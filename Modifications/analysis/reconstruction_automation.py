''' For a given reconstruction binary, call it with combinations of sample size, model etc. '''

import json

def main():
    fp = open("config.json")
    config = json.load(fp)

if __name__ == "__main__":
    main()