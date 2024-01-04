#!/bin/bash

if [ -f sum.cpp ]; then
    rm sum.cpp
fi

printf "#define ASSIGN4_INTEGRATED\n" > sum.cpp

{
  cat src/util.hpp
  cat src/card.hpp
  cat src/player.hpp
  cat src/game.hpp
  cat src/card.cpp
  cat src/player.cpp
  cat src/game.cpp
} >> sum.cpp


if [ -f sum.cpp ]; then
    echo "The files have been concatenated into sum.cpp successfully."
else
    echo "There was an error creating sum.cpp."
fi

