//
// Created by jules on 01/06/23.
//

#include "centersCSV.hpp"

centersCSV::centersCSV(const std::string &path) {
  int i = 0; // Iterator for the rows
  int j; // Iterator for the columns

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
        this->id.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else {
        this->name.push_back(field.get<std::string>()); // Add a new field, push back the value of the field and convert it to string
      }
      j++;
    }
    i++;
  }
  this->nbCenters = i; // Set the number of centers
}

centersCSV::~centersCSV() {

}

std::vector<int> centersCSV::getId() {
  return this->id;
}

std::vector<std::string> centersCSV::getName() {
  return this->name;
}

void centersCSV::printId() {
  for (int i = 0; i < this->nbCenters; i++) {
    std::cout << this->id[i] << std::endl;
  }
}

void centersCSV::printName() {
  for (int i = 0; i < this->nbCenters; i++) {
    std::cout << this->name[i] << std::endl;
  }
}

void centersCSV::printCenters() {
  for (int i = 0; i < this->nbCenters; i++) {
    std::cout << this->id[i] << " " << this->name[i] << std::endl;
  }
}
