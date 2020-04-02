#!/usr/bin/env python3
# -*- coding:utf-8 -*-

__author__    = 'Mu Yang <http://muyang.pro>'
__copyright__ = 'Copyright 2020'

import glob
import os

LANG = {
    '.cpp': 'C++',
    '.py': 'Python',
    '.sh': 'Bash',
}

def main():

    with open('./README.md', 'w') as fout:

        # Header
        print('# LeetCode', file=fout)
        print('LeetCode Problems\' Solutions', file=fout)
        print(file=fout)

        # Categories
        for cat_dir in sorted(glob.glob('./problems/*')):
            cat = os.path.basename(cat_dir).capitalize()
            print(f'# {cat}', file=fout)
            print(file=fout)

            # Table
            print('| # | Title | Solution | Difficulty |', file=fout)
            print('|---| ----- | -------- | ---------- |', file=fout)
            for prob_file in sorted(glob.glob(f'{cat_dir}/*')):
                prob_num, prob_lang = os.path.splitext(os.path.basename(prob_file))
                prob_num = int(prob_num)
                prob_lang = LANG[prob_lang]
                with open(prob_file) as fin:
                    prob_source = fin.readline().split(':')[-1].strip()
                    prob_title = fin.readline().split(':')[-1].strip()
                    prob_diff = fin.readline().split(':')[-1].strip()

                print(f'| {prob_num} | [{prob_title}]({prob_source}) | [{prob_lang}]({prob_file}) | {prob_diff} |', file=fout)
            print(file=fout)

if __name__ == '__main__':
    main()
