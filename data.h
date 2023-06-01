//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_DATA_H
#define IT45_PROJECT_DATA_H

#include <iostream>
#include <vector>
#include "classes/center.h"

class data {

  std::vector<center *> centers;
  int nbCenters;

  std::vector<mission *> missions;
  int nbMissions;

  std::vector<std::vector<float>> matrix; // 2D vector of floats to store the matrix
  int nbRows;                             // Number of rows of the matrix
  int nbColumns;                          // Number of columns of the matrix

  friend class dataAnalysis;
};


#endif //IT45_PROJECT_DATA_H
