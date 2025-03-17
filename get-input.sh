#!/usr/bin/env bash
set -eo pipefail

# Obtain the variables
if test -z "$YEAR"; then read -ep 'Year? ' YEAR; fi
if test -z "$DAY"; then read -ep 'Day? ' DAY; fi
if test -z "$SESSION"; then read -ep 'Session? ' SESSION; fi

# Make the parent directories
mkdir -p "inputs/$YEAR"

# Finally get the file
curl -L --cookie "session=$SESSION" "https://adventofcode.com/$YEAR/day/$DAY/input" -o "inputs/$YEAR/$DAY"
