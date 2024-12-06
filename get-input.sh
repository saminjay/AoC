#!/usr/bin/env bash

if [[ $# -ne 2 ]]; then
    echo "Requires 2 arguments:"
    echo "    1. year (e.g. 2024)"
    echo "    2. day (e.g. 5)"
    exit 1
fi

source .env

input=$(curl "https://adventofcode.com/$1/day/$2/input" \
    -H "Cookie: session=$SESSION_ID")

dir=$(printf "%d/day-%02d" "$1" "$2")
mkdir -p "$dir"
echo "$input" >"$dir/input.txt"
cp "template/template.cpp" "$dir/soln.cpp"
