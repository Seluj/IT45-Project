/**
 * @file employee.hpp
 * @brief Header file for class employee
 * @date 01/06/2021
 *
 * Header file containing the definition of the class employee
 * This class is used to store the data of an employee
 */

#ifndef IT45_PROJECT_EMPLOYEE_HPP
#define IT45_PROJECT_EMPLOYEE_HPP

#include <iostream>
#include <vector>

/**
 * @class employee
 * @brief Class representing an employee
 */
class employee {
private:
  int id;
  int idCenter;
  std::string skill;
  std::string speciality;

  public:
    employee();
    employee(int id, int idCenter, std::string skill, std::string speciality);
    ~employee();
    int getId();
    int getIdCenter();
    std::string getSkill();
    std::string getSpeciality();
    void printEmployee();
};


#endif //IT45_PROJECT_EMPLOYEE_HPP
