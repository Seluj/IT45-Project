//
// Created by jules on 01/06/2023.
//

#ifndef IT45_PROJECT_CENTER_HPP
#define IT45_PROJECT_CENTER_HPP

#include <iostream>
#include <vector>
#include "employee.hpp"
#include "mission.hpp"

class center {
private:
  int id;
  std::string name;
  int capacity;

  std::vector<employee*> employeesLSF;
  int nbEmployeesLSF;
  std::vector<employee*> employeesLCP;
  int nbEmployeesLCP;
  std::vector<mission*> missionsLSF;
  int nbMissionsLSF;
  std::vector<mission*> missionsLCP;
  int nbMissionsLCP;

public:
  center();
  center(int id, std::string name);
  ~center();

  void printCenter();

  void addEmployeeLSF(employee* employee);
  void addEmployeeLCP(employee* employee);
  void addMissionLSF(mission* mission);
  void addMissionLCP(mission* mission);
};


#endif //IT45_PROJECT_CENTER_HPP
