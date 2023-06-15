#!/bin/bash

MAIN=main
ARG=$1


echo -e "\n\n"
echo "===================================================="
echo "            Project by Céliane and Jules            "
echo "                                                    "
echo "                        P23                         "
echo "                                                    "
echo "                      Use help                      "
echo "===================================================="
echo -e "\n\n"

echo "Press enter to continue"
read -r
echo -e "\n\n"

if [ ! -f "$MAIN" ]; then
  echo "$MAIN does not exists"
  echo -e "Would you like to compile the project? (yes or no)\n"
  read -r answer
  while [ "$answer" != "yes" ] && [ "$answer" != "no" ]; do
    echo -e "You have to answer yes or no\n"
    read -r answer
  done

  if [ "$answer" == "yes" ]; then
    ./build.sh "clean"
  else
    echo "===================================================="
    echo "                      ok, bye                       "
    echo "===================================================="
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

if [ "$ARG" == "help" ]; then
  echo "Usage: ./run.sh [path]"
  echo "path: path to input files"
  echo "If you do not pass any argument, the default path is ./instances/200Missions-2centres/"
  exit
fi

if [ ! -d "$ARG" ]; then
  echo "$ARG does not exists"
  echo "Use help for more information"
  exit
fi

echo "Run the project"
echo "Input file: $ARG"
./main "$ARG"
