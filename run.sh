#!/bin/bash

MAIN=main
ARG=$1

if [ ! -f "$MAIN" ]; then
  echo "$MAIN does not exists"
  echo "Would you like to compile the project? (yes or no)"
  read -r answer
  while [ "$answer" != "yes" ] && [ "$answer" != "no" ]
  do
    echo "You have to answer yes or no"
    read -r answer
  done

  if [ "$answer" == "yes" ]; then
    ./build.sh "clean"
  else
    echo "ok"
    exit
  fi
else
  ./build.sh
fi

if [[ -z "$ARG" ]]; then
  echo "You do not pass any argument"
  echo "Take default path for input file"
  echo "./instances/200Missions-2centres/"
  ARG="./instances/200Missions-2centres/"
fi

if [ ! -d "$ARG" ]; then
  echo "$ARG does not exists"
  exit
fi

echo "Run the project"
echo "Input file: $ARG"
./main "$ARG"