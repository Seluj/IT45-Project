#!/usr/bin/env bash

ARG=$1

if [ "$ARG" == "clean" ]; then
  echo "Clean the project"
  make clean
fi

echo "Building the project"
make