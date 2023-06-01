//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_EMPLOYEESCSV_HPP
#define IT45_PROJECT_EMPLOYEESCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"
#include "../classes/employee.h"

class employeesCSV {
  private:
    std::vector<employee *> employees;
    int nbEmployees;

  public:
    employeesCSV(const std::string& path);
    ~employeesCSV();

    std::vector<employee *> getEmployees();
    int getNbEmployees();

    void printEmployees();
};


#endif //IT45_PROJECT_EMPLOYEESCSV_HPP
