/**
 * @file distances.h
 * @brief Header file for class distances
 * @date 02/06/2023
 *
 * Header file containing the definition of the class distances
 */

#ifndef IT45_PROJECT_DISTANCES_H
#define IT45_PROJECT_DISTANCES_H

#include "../inclusion.hpp"

/**
 * @class distances
 * @brief Class used to store the distances between the different missions and centers
 */
class distances {

private:

  std::vector<std::vector<float>> matrix; // 2D vector of floats to store the matrix
  int nbRows;                             // Number of rows of the matrix
  int nbColumns;                          // Number of columns of the matrix

public:

  distances(std::vector<std::vector<float>> matrix, int nbRows, int nbColumns);

  float getDistance(int row, int column);

  std::vector<std::vector<float>> getMatrix();

  void printMatrix();
};


#endif //IT45_PROJECT_DISTANCES_H
