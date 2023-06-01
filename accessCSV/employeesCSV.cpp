//
// Created by jules on 01/06/23.
//

#include "employeesCSV.hpp"

employeesCSV::employeesCSV(const std::string &path) {
  int i = 0;
  int j = 0;

  // Set the format of the CSV file
  csv::CSVFormat format;
  format.delimiter(',').no_header();

  // Read the CSV file
  csv::CSVReader reader(path + "/Employees.csv", format);

  // Store the matrix in a 2D vector
  for (csv::CSVRow& row: reader) { // Input iterator for the rows
    j = 0;
    for (csv::CSVField& field: row) { // Input iterator for the fields
      if (j == 0) {
        this->id.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 1) {
        this->idCenter.push_back(field.get<int>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 2) {
        this->skill.push_back(field.get<std::string>()); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 3) {
        this->speciality.push_back(field.get<std::string>()); // Add a new field, push back the value of the field and convert it to string
      }
      j++;
    }
    i++;
  }
  this->nbEmployees = i; // Set the number of employees
}

employeesCSV::~employeesCSV() = default;

std::vector<int> employeesCSV::getId() {
  return this->id;
}

std::vector<int> employeesCSV::getIdCenter() {
  return this->idCenter;
}

std::vector<std::string> employeesCSV::getSkill() {
  return this->skill;
}

std::vector<std::string> employeesCSV::getSpeciality() {
  return this->speciality;
}

void employeesCSV::printId() {
  for (int i = 0; i < this->nbEmployees; i++) {
    std::cout << this->id[i] << std::endl;
  }
}

void employeesCSV::printIdCenter() {
  for (int i = 0; i < this->nbEmployees; i++) {
    std::cout << this->idCenter[i] << std::endl;
  }
}

void employeesCSV::printSkill() {
  for (int i = 0; i < this->nbEmployees; i++) {
    std::cout << this->skill[i] << std::endl;
  }
}

void employeesCSV::printSpeciality() {
  for (int i = 0; i < this->nbEmployees; i++) {
    std::cout << this->speciality[i] << std::endl;
  }
}

void employeesCSV::printEmployees() {
  for (int i = 0; i < this->nbEmployees; i++) {
    std::cout << this->id[i] << " " << this->idCenter[i] << " " << this->skill[i] << " " << this->speciality[i] << std::endl;
  }
}
