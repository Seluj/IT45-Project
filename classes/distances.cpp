//
// Created by jules on 02/06/2023.
//

#include "distances.hpp"

/* --------------------------------- Constructor --------------------------------- */

distances::distances(std::vector<std::vector<float>> matrix, int nbRows, int nbColumns) {
  this->matrix = std::move(matrix);
  this->nbRows = nbRows;
  this->nbColumns = nbColumns;
}

/* --------------------------------- Getters --------------------------------- */

float distances::getDistance(int row, int column) {
  return matrix[row][column];
}


std::vector<std::vector<float>> distances::getMatrix() {
  return this->matrix;
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

/* --------------------------------- Modify the matrix --------------------------------- */

void distances::modifyElement(int i, int j, float value) {
  this->matrix[i][j] = value;
}

void distances::modifyRow(int i, float value) {
  for (int j = 0; j < this->nbColumns; j++) {
    this->matrix[i][j] = value;
  }
}

void distances::modifyRow(int i, std::vector<float> row) {
  this->matrix[i] = std::move(row);
}

void distances::mofifyColumn(int j, float value) {
  for (int i = 0; i < this->nbRows; i++) {
    this->matrix[i][j] = value;
  }
}

void distances::mofifyColumn(int j, std::vector<float> column) {
  for (int i = 0; i < this->nbRows; i++) {
    this->matrix[i][j] = column[i];
  }
}
