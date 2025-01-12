#!/usr/bin/env bash

function validate-input() {
    if [[ $# -ne 2 ]]; then
        echo "Requires 2 arguments:"
        echo "    1. year (e.g. 2024)"
        echo "    2. day (e.g. 5)"
        exit 1
    fi

    local curr_year
    curr_year=$(date +%Y)

    if [[ $1 -lt 2015 || $1 -gt $curr_year ]]; then
        echo "Year should be in between 2015 and $curr_year"
        exit 1
    fi

    if [[ $2 -lt 1 || $2 -gt 25 ]]; then
        echo "Day should be in between 1 and 25"
        exit 1
    fi

    year=$1
    day=$2
}

function get-input() {
    local input
    input=$(curl "https://adventofcode.com/$year/day/$day/input" \
        -H "Cookie: session=$SESSION_ID")

    local dir
    dir=$(cd -- "$(dirname "$0")" && pwd)
    dir=$(printf "%s/%d/day-%02d" "$dir" "$year" "$day")

    mkdir -p "$dir/cpp"
    echo "$input" >"$dir/input.txt"
    cp "template/template.cpp" "$dir/cpp/soln.cpp"
}

function main() {
    local day
    local year
    source .env
    validate-input "$@"
    get-input
}

main "$@"
