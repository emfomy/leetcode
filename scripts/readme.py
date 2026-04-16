#!/usr/bin/env python3
# -*- coding:utf-8 -*-

__author__ = "Mu Yang <http://muyang.pro>"
__copyright__ = "Copyright 2025"

import glob
import os
import sys

LANG = {
    "c": "C",
    "cpp": "C++",
    "go": "Go",
    "py": "Python",
    "sql": "SQL",
    "sh": "Bash",
}


def myprint(*args, file=None, **kwargs):
    print(*args, **kwargs)
    if file is not None:
        print(*args, **kwargs, file=file)


def main():

    data = {}
    errors = []

    for prob_dir in sorted(glob.glob("problems/*-*")):
        if not os.path.isdir(prob_dir):
            errors.append(f"Expected {prob_dir} to be a directory")
            continue

        basename = os.path.basename(prob_dir)
        prob_num_str, lang_code = basename.split("-", 1)
        prob_num = int(prob_num_str)

        filepath = os.path.join(prob_dir, f"main.{lang_code}")
        if not os.path.isfile(filepath):
            errors.append(f"Expected {filepath} to exist")
            continue

        prob_lang = LANG.get(lang_code)
        if not prob_lang:
            errors.append(f"Unknown lang_code: {lang_code}")
            continue

        with open(filepath) as fin:
            prob_source = fin.readline().split(":", 1)[-1].strip()
            prob_title = fin.readline().split(":", 1)[-1].strip()
            prob_difficulty = fin.readline().split(":", 1)[-1].strip()

        if prob_num not in data:
            data[prob_num] = {
                "source": prob_source,
                "title": prob_title,
                "difficulty": prob_difficulty,
                "solution": {
                    prob_lang: filepath,
                },
            }
        else:
            prob = data[prob_num]
            if prob["source"] != prob_source:
                errors.append(f"Problem {prob_num}: source mismatch ({prob['source']!r} vs {prob_source!r})")
            if prob["title"] != prob_title:
                errors.append(f"Problem {prob_num}: title mismatch ({prob['title']!r} vs {prob_title!r})")
            if prob["difficulty"] != prob_difficulty:
                errors.append(f"Problem {prob_num}: difficulty mismatch ({prob['difficulty']!r} vs {prob_difficulty!r})")
            prob["solution"][prob_lang] = filepath

    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        sys.exit(1)

    with open("./README.md", "w") as fout:

        # Header
        myprint("# LeetCode", file=fout)
        myprint("LeetCode Problems' Solutions", file=fout)
        myprint(file=fout)
        myprint("# Problems", file=fout)
        myprint(file=fout)

        # Table
        myprint("| # | Title | Solution | Difficulty |", file=fout)
        myprint("|---| ----- | -------- | ---------- |", file=fout)
        for prob_num in sorted(data.keys()):
            prob = data[prob_num]
            prob_title = prob["title"]
            prob_source = prob["source"]
            prob_difficulty = prob["difficulty"]
            solutions = " ".join(
                (f"[{lang}]({file})" for lang, file in sorted(prob["solution"].items()))
            )
            myprint(
                f"| {prob_num} | [{prob_title}]({prob_source}) | {solutions} | {prob_difficulty} |",
                file=fout,
            )
        myprint(file=fout)


if __name__ == "__main__":
    main()
