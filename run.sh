#!/bin/bash

MAIN=main
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
    ./build.sh
  else
    echo "ok"
    exit
  fi
fi

