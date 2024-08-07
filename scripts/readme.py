#!/usr/bin/env python3
# -*- coding:utf-8 -*-

__author__    = 'Mu Yang <http://muyang.pro>'
__copyright__ = 'Copyright 2020'

import glob
import os

LANG = {
    '.c': 'C',
    '.cpp': 'C++',
    '.go': 'Go',
    '.py': 'Python',
    '.sh': 'Bash',
}

def myprint(*args, file=None, **kwargs):
    print(*args, **kwargs)
    print(*args, **kwargs, file=file)

def main():

    data = {}

    for prob_file in sorted(glob.glob('problems/*')):
        prob_num, prob_lang = os.path.splitext(os.path.basename(prob_file))
        prob_num = int(prob_num)
        prob_lang = LANG[prob_lang]
        with open(prob_file) as fin:
            prob_source = fin.readline().split(':')[-1].strip()
            prob_title = fin.readline().split(':')[-1].strip()
            prob_difficulty = fin.readline().split(':')[-1].strip()

        if prob_num not in data:
            data[prob_num] = {
                'source': prob_source,
                'title': prob_title,
                'difficulty': prob_difficulty,
                'solution': {
                    prob_lang: prob_file,
                }
            }
        else:
            prob = data[prob_num]
            assert prob['source'] == prob_source, prob
            assert prob['title'] == prob_title, prob
            assert prob['difficulty'] == prob_difficulty, prob
            prob['solution'][prob_lang] = prob_file

    with open('./README.md', 'w') as fout:

        # Header
        myprint('# LeetCode', file=fout)
        myprint('LeetCode Problems\' Solutions', file=fout)
        myprint(file=fout)
        myprint('# Problems', file=fout)
        myprint(file=fout)

        # Table
        myprint('| # | Title | Solution | Difficulty |', file=fout)
        myprint('|---| ----- | -------- | ---------- |', file=fout)
        for prob_num in sorted(data.keys()):
            prob = data[prob_num]
            prob_title = prob['title']
            prob_source = prob['source']
            prob_difficulty = prob['difficulty']
            solutions = ' '.join((f'[{lang}]({file})' for lang, file in sorted(prob['solution'].items())))
            myprint(f'| {prob_num} | [{prob_title}]({prob_source}) | {solutions} | {prob_difficulty} |', file=fout)
        myprint(file=fout)

if __name__ == '__main__':
    main()
