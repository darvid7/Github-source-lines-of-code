#!/usr/bin/env bash
git clone --depth 1 "$1" temp-linecount-repo &&
  printf "(processing repo: "$1")\n\n" &&
  cloc temp-linecount-repo --json --report-file=data.json &&
  rm -rf temp-linecount-repo
