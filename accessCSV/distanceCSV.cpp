/**
 * @file distanceCSV.cpp
 * @brief Implementation of the distanceCSV class
 * @date 01/06/2023
 */

#include "distanceCSV.hpp"

/* --------------------------------- Constructor --------------------------------- */

distanceCSV::distanceCSV(const std::string &path) {
  std::vector<std::vector<float>> matrix; // 2D vector of floats to store the matrix
  int i = 0;                              // Iterator for the rows

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/Distances.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow &row: reader) { // Input iterator for the rows
    matrix.emplace_back(); // Add a new row
    for (csv::CSVField &field: row) { // Input iterator for the fields
      matrix[i].push_back(
        field.get<float>()); // Add a new field, push back the value of the field and convert it to float
    }
    i++;
  }

  this->distancesMatrix = new distances(matrix, i, matrix[0].size()); // Create a new distances object
}

/* --------------------------------- Destructor --------------------------------- */

distanceCSV::~distanceCSV() = default;


/* --------------------------------- Print Method --------------------------------- */

void distanceCSV::printMatrix() {
  this->distancesMatrix->printMatrix();
}

distances *distanceCSV::getDistancesMatrix() {
  return this->distancesMatrix;
}


