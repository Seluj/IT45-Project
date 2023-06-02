/**
 * @file distanceCSV.cpp
 * @brief Implementation of the distanceCSV class
 * @date 01/06/2023
 */

#include "employeesCSV.hpp"

/* --------------------------------- Constructor --------------------------------- */

employeesCSV::employeesCSV(const std::string &path) {
  int i = 0;                // Iterator for the rows
  int j = 0;                // Iterator for the columns
  int id;                   // Id of the employee
  int idCenter;             // Id of the center
  std::string skill;        // Name of the center
  std::string speciality;   // Name of the center

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
        id = field.get<int>(); // Convert the field to int and store it in id
      } else if (j == 1) {
        idCenter = field.get<int>(); // Convert the field to int and store it in idCenter
      } else if (j == 2) {
        skill = field.get<std::string>(); // Convert the field to string and store it in skill
      } else if (j == 3) {
        speciality = field.get<std::string>(); // Convert the field to string and store it in speciality
      }
      j++;
    }
    this->employees.push_back(new employee(id, idCenter, skill, speciality)); // Add a new employee to the vector
    i++;
  }
  this->nbEmployees = i; // Set the number of employees
}

/* --------------------------------- Destructor --------------------------------- */

employeesCSV::~employeesCSV() = default;

/* --------------------------------- accessors --------------------------------- */

std::vector<employee *> employeesCSV::getEmployees() {
  return this->employees;
}

int employeesCSV::getNbEmployees() {
  return this->nbEmployees;
}

/* --------------------------------- Print Method --------------------------------- */

void employeesCSV::printEmployees() {
  for (int i = 0; i < this->nbEmployees; i++) {
    this->employees[i]->printEmployee();
  }
}
