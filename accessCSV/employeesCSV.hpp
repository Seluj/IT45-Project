//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_EMPLOYEESCSV_HPP
#define IT45_PROJECT_EMPLOYEESCSV_HPP

#include <iostream>
#include <vector>
#include "../csv.hpp"

class employeesCSV {
  private:
    std::vector<int> id;
    std::vector<int> idCenter;
    std::vector<std::string> skill;
    std::vector<std::string> speciality;
    int nbEmployees;

  public:
    employeesCSV(const std::string& path);
    ~employeesCSV();
    std::vector<int> getId();
    std::vector<int> getIdCenter();
    std::vector<std::string> getSkill();
    std::vector<std::string> getSpeciality();
    void printId();
    void printIdCenter();
    void printSkill();
    void printSpeciality();
    void printEmployees();
};


#endif //IT45_PROJECT_EMPLOYEESCSV_HPP
