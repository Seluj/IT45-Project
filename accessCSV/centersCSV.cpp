//
// Created by jules on 01/06/23.
//

#include "centersCSV.hpp"

centersCSV::centersCSV(const std::string &path) {
  int i = 0; // Iterator for the rows
  int j; // Iterator for the columns
  int id;
  std::string name;

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/centers.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    j = 0;
    for (csv::CSVField& field: row) { // Input iterator for the fields
      if (j == 0) {
        id = field.get<int>(); // Add a new field, push back the value of the field and convert it to int
      } else {
        name = field.get<std::string>(); // Add a new field, push back the value of the field and convert it to string
      }
      j++;
    }
    this->centers.push_back(new center(id, name)); // Add a new center to the vector
    i++;
  }
  this->nbCenters = i; // Set the number of centers
}

centersCSV::~centersCSV() = default;

void centersCSV::printCenters() {
  for (int i = 0; i < this->nbCenters; i++) {
    this->centers[i]->printCenter();
  }
}

std::vector<center *> centersCSV::getCenters() {
  return this->centers;
}

int centersCSV::getNbCenters() {
  return this->nbCenters;
}
