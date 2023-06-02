/**
 * @file center.cpp
 * @brief Source file for class center
 * @date 02/06/2023
 *
 * All the methods of the class center are here
 */

#include "center.hpp"

#include <utility>

center::center() {
  id = 0;
  name = "";
  capacity = 0;
  nbEmployeesLSF = 0;
  nbEmployeesLCP = 0;
  nbMissionsLSF = 0;
  nbMissionsLCP = 0;
}

center::center(int id, std::string name) {
  this->id = id;
  this->name = std::move(name);
  capacity = 0;
  nbEmployeesLSF = 0;
  nbEmployeesLCP = 0;
  nbMissionsLSF = 0;
  nbMissionsLCP = 0;
}

center::~center() = default;

void center::printCenter() {
  std::cout << "Center " << this->id << " " << this->name << std::endl;
  std::cout << "Capacity: " << this->capacity << std::endl;
  std::cout << "Employees LSF: " << this->nbEmployeesLSF << std::endl;
  std::cout << "Employees LCP: " << this->nbEmployeesLCP << std::endl;
  std::cout << "Missions LSF: " << this->nbMissionsLSF << std::endl;
  std::cout << "Missions LCP: " << this->nbMissionsLCP << std::endl;
  std::cout << std::endl;
}

void center::addEmployeeLSF(employee *employee) {
  this->employeesLSF.push_back(employee);
  this->nbEmployeesLSF++;
}

void center::addEmployeeLCP(employee *employee) {
  this->employeesLCP.push_back(employee);
  this->nbEmployeesLCP++;
}

void center::addMissionLSF(mission *mission) {
  this->missionsLSF.push_back(mission);
  this->nbMissionsLSF++;
}

void center::addMissionLCP(mission *mission) {
  this->missionsLCP.push_back(mission);
  this->nbMissionsLCP++;
}
