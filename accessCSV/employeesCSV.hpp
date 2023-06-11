/**
 * @file employeesCSV.hpp
 * @brief Header file for class employeesCSV
 * @date 01/06/2023
 *
 * Header file containing the definition of the class employeesCSV
 * This class is used to read the employees.csv file and store the data in a vector of pointers to employee objects
 */

#ifndef IT45_PROJECT_EMPLOYEESCSV_HPP
#define IT45_PROJECT_EMPLOYEESCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"
#include "../classes/employee.hpp"

/**
 * @class employeesCSV
 * @brief Class used to read the employees.csv file and store the data in a vector of pointers to employee objects
 */
class employeesCSV {

private:
  std::vector<employee *> employees;  // Vector of pointers to employee objects
  int nbEmployees;                    // Number of employees

public:

  /* --------------------------------- Constructor --------------------------------- */

  employeesCSV(const std::string &path);

  /* --------------------------------- Destructor --------------------------------- */

  ~employeesCSV();

  /* --------------------------------- Accessors --------------------------------- */

  std::vector<employee *> getEmployees();

  int getNbEmployees();

  /* --------------------------------- Print Method --------------------------------- */

  void printEmployees();
};


#endif //IT45_PROJECT_EMPLOYEESCSV_HPP
