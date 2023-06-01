//
// Created by jules on 01/06/23.
//

#include "employeesCSV.hpp"

employeesCSV::employeesCSV(const std::string &path) {
  int i = 0;
  int j = 0;
  int id;
  int idCenter;
  std::string skill;
  std::string speciality;

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
        id = field.get<int>(); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 1) {
        idCenter = field.get<int>(); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 2) {
        skill = field.get<std::string>(); // Add a new field, push back the value of the field and convert it to int
      } else if (j == 3) {
        speciality = field.get<std::string>(); // Add a new field, push back the value of the field and convert it to string
      }

      j++;
    }
    this->employees.push_back(new employee(id, idCenter, skill, speciality));
    i++;
  }
  this->nbEmployees = i; // Set the number of employees
}

employeesCSV::~employeesCSV() = default;

void employeesCSV::printEmployees() {
  for (int i = 0; i < this->nbEmployees; i++) {
    this->employees[i]->printEmployee();
  }
}

std::vector<employee *> employeesCSV::getEmployees() {
  return this->employees;
}

int employeesCSV::getNbEmployees() {
  return this->nbEmployees;
}
