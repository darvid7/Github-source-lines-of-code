#!/usr/bin/env bash
git clone --depth 1 "$1" temp-linecount-repo -q &&
  cloc temp-linecount-repo --json --report-file="./data/data.json" --quiet &&
  rm -rf temp-linecount-repo
