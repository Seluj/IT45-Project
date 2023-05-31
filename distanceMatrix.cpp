//
// Created by jules on 31/05/2023.
//

#include "distanceMatrix.h"

#include <utility>

distanceMatrix::distanceMatrix(const std::string &path) {
  int i = 0; // Iterator for the rows

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/distances.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    this->matrix.emplace_back(); // Add a new row
    for (csv::CSVField& field: row) { // Input iterator for the fields
      this->matrix[i].push_back(field.get<float>()); // Add a new field, push back the value of the field and convert it to float
    }
    i++;
  }
  this->nbRows = i;                          // Set the number of rows
  this->nbColumns = this->matrix[0].size();  // Set the number of columns
}

distanceMatrix::~distanceMatrix() = default;

void distanceMatrix::printMatrix() {
  for (int i = 0; i < this->nbRows; i++) {
    std::cout << i << " : ";
    for (int j = 0; j < this->nbColumns; j++) {
      std::cout << this->matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<float>> distanceMatrix::getMatrix() {
  return this->matrix;
}

int distanceMatrix::getNbRows() {
  return this->nbRows;
}

int distanceMatrix::getNbColumns() {
  return this->nbColumns;
}

void distanceMatrix::modifyElement(int i, int j, float value) {
  this->matrix[i][j] = value;
}

void distanceMatrix::modifyRow(int i, float value) {
  for (int j = 0; j < this->nbColumns; j++) {
    this->matrix[i][j] = value;
  }
}

void distanceMatrix::modifyRow(int i, std::vector<float> row) {
  this->matrix[i] = std::move(row);
}

void distanceMatrix::mofifyColumn(int j, float value) {
  for (int i = 0; i < this->nbRows; i++) {
    this->matrix[i][j] = value;
  }
}

void distanceMatrix::mofifyColumn(int j, std::vector<float> column) {
  for (int i = 0; i < this->nbRows; i++) {
    this->matrix[i][j] = column[i];
  }
}
