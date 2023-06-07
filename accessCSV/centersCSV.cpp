/**
 * @file centersCSV.cpp
 * @brief Implementation of the centersCSV class
 * @date 01/06/2023
 */

#include "centersCSV.hpp"

/* --------------------------------- Constructor --------------------------------- */

centersCSV::centersCSV(const std::string &path) {
  int i = 0;        // Iterator for the rows
  int j;            // Iterator for the columns
  int id;           // Id of the center
  std::string name; // Name of the center

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/Centers.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    j = 0;
    for (csv::CSVField& field: row) { // Input iterator for the fields
      if (j == 0) {
        id = field.get<int>(); // Convert the field to int and store it in id
      } else {
        name = field.get<std::string>(); // Convert the field to string and store it in name
      }
      j++;
    }
    this->centers.push_back(new center(id, name)); // Add a new center to the vector
    i++;
  }
  this->nbCenters = i; // Set the number of centers
}

/* --------------------------------- Destructor --------------------------------- */

centersCSV::~centersCSV() = default;

/* --------------------------------- accessors --------------------------------- */

std::vector<center *> centersCSV::getCenters() {
  return this->centers;
}

int centersCSV::getNbCenters() {
  return this->nbCenters;
}

/* --------------------------------- Print Method --------------------------------- */

void centersCSV::printCenters() {
  for (int i = 0; i < this->nbCenters; i++) {
    this->centers[i]->printCenter();
  }
}
