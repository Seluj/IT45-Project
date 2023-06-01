//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_EMPLOYEE_H
#define IT45_PROJECT_EMPLOYEE_H

#include <iostream>
#include <vector>

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

  employee(std::vector<employee *> vector1);
};


#endif //IT45_PROJECT_EMPLOYEE_H
