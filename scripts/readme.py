#!/usr/bin/env python3
# -*- coding:utf-8 -*-

__author__ = "Mu Yang <http://muyang.pro>"
__copyright__ = "Copyright 2025"

import glob
import os

LANG = {
    ".c": "C",
    ".cpp": "C++",
    ".go": "Go",
    ".py": "Python",
    ".sh": "Bash",
}


def myprint(*args, file=None, **kwargs):
    print(*args, **kwargs)
    print(*args, **kwargs, file=file)


def main():

    data = {}

    for prob_dir in sorted(glob.glob("problems/*-*")):
        if not os.path.isdir(prob_dir):
            continue

        basename = os.path.basename(prob_dir)
        if "-" not in basename:
            continue

        prob_num_str, lang_code = basename.split("-", 1)
        try:
            prob_num = int(prob_num_str)
        except ValueError:
            continue

        # Try to find the main source file
        files = [f for f in os.listdir(prob_dir) if f.startswith("main.")]
        if not files:
            continue

        filename = files[0]
        filepath = os.path.join(prob_dir, filename)
        ext = os.path.splitext(filename)[-1]

        prob_lang = LANG.get(ext)
        if not prob_lang:
            continue

        with open(filepath) as fin:
            try:
                prob_source = fin.readline().split(":", 1)[-1].strip()
                prob_title = fin.readline().split(":", 1)[-1].strip()
                prob_difficulty = fin.readline().split(":", 1)[-1].strip()
            except Exception:
                continue

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
            assert prob["source"] == prob_source, prob
            assert prob["title"] == prob_title, prob
            assert prob["difficulty"] == prob_difficulty, prob
            prob["solution"][prob_lang] = filepath

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
