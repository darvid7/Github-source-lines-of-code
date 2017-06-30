#!/usr/bin/env bash
git clone --depth 1 "$1" temp-sloc-count-repo --quiet 2> gitwarnings.txt &&
  cloc temp-sloc-count-repo --json --report-file="./data/data.json" --quiet  &&
  rm -rf temp-sloc-count-repo
