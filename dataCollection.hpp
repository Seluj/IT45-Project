//
// Created by jules on 01/06/23.
//

#ifndef IT45_PROJECT_DATACOLLECTION_HPP
#define IT45_PROJECT_DATACOLLECTION_HPP

#include "accessCSV/distanceCSV.hpp"
#include "accessCSV/centersCSV.hpp"
#include "accessCSV/missionsCSV.hpp"
#include "accessCSV/employeesCSV.hpp"

class dataCollection {
private:
  distanceCSV* distance;
  centersCSV* centers;
  missionsCSV* missions;
  employeesCSV* employees;

public:
  dataCollection(const std::string& path);
  ~dataCollection();
  distanceCSV* getDistance();
  centersCSV* getCenters();
  missionsCSV* getMissions();
  employeesCSV* getEmployees();

  void printDataCollection();
};


#endif //IT45_PROJECT_DATACOLLECTION_HPP
