/**
 * @file center.cpp
 * @brief Source file for class center
 * @date 02/06/2023
 *
 * All the methods of the class center are here
 */

#include "center.hpp"

#include <utility>

/* --------------------------------- Constructor --------------------------------- */

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
  this->name = std::move(name); // Move the string instead of copying it (more efficient)
  capacity = 0;
  nbEmployeesLSF = 0;
  nbEmployeesLCP = 0;
  nbMissionsLSF = 0;
  nbMissionsLCP = 0;
}

/* --------------------------------- Destructor --------------------------------- */

center::~center() = default;

/* --------------------------------- accessors --------------------------------- */


/* --------------------------------- Print Method --------------------------------- */

void center::printCenter() {
  std::cout << "Center : " << this->id << " " << this->name << std::endl;
  std::cout << "Capacity: " << this->capacity << std::endl;
  std::cout << "Employees LSF: " << this->nbEmployeesLSF << std::endl;
  std::cout << "Employees LCP: " << this->nbEmployeesLCP << std::endl;
  std::cout << "Missions LSF: " << this->nbMissionsLSF << std::endl;
  std::cout << "Missions LCP: " << this->nbMissionsLCP << std::endl;
  std::cout << std::endl;
}

/* --------------------------------- add employee/mission --------------------------------- */

void center::addEmployeeLSF(employee *employee) {
  this->employeesLSF.push_back(employee); // add the employee to the vector
  this->nbEmployeesLSF++;                 // increment the number of employees
}

void center::addEmployeeLCP(employee *employee) {
  this->employeesLCP.push_back(employee); // add the employee to the vector
  this->nbEmployeesLCP++;                 // increment the number of employees
}

void center::addMissionLSF(mission *mission) {
  this->missionsLSF.push_back(mission); // add the mission to the vector
  this->nbMissionsLSF++;                // increment the number of missions
}

void center::addMissionLCP(mission *mission) {
  this->missionsLCP.push_back(mission); // add the mission to the vector
  this->nbMissionsLCP++;                // increment the number of missions
}
