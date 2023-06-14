/**
 * @file distances.cpp
 * @brief Source file for class distances
 * @date 02/06/2023
 *
 * All the methods of the class distances are here
 */

#include "distances.hpp"

/* --------------------------------- Constructor --------------------------------- */

distances::distances(std::vector<std::vector<float>> matrix, int nbRows, int nbColumns) {
  this->matrix = matrix;
  this->nbRows = nbRows;
  this->nbColumns = nbColumns;
}

/* --------------------------------- Getters --------------------------------- */

float distances::getDistance(int row, int column) {
  return matrix[row][column];
}

/* --------------------------------- Print the matrix --------------------------------- */

void distances::printMatrix() {
  for (int i = 0; i < this->nbRows; i++) {
    for (int j = 0; j < this->nbColumns; j++) {
      std::cout << this->matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
