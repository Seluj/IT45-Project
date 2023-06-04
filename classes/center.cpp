/**
 * @file center.cpp
 * @brief Source file for class center
 * @date 02/06/2023
 *
 * All the methods of the class center are here
 */

#include "center.hpp"

/* --------------------------------- Constructor --------------------------------- */

center::center() {
  id = 0;
  name = "";
  capacity.clear();
  startingPeriodForPrinting.clear();
}

center::center(int id, std::string name) {
  this->id = id;
  this->name = std::move(name); // Move the string instead of copying it (more efficient)
  capacity.clear();
  startingPeriodForPrinting.clear();
}

/* --------------------------------- Destructor --------------------------------- */

center::~center() = default;

/* --------------------------------- accessors --------------------------------- */


/* --------------------------------- Print Method --------------------------------- */

void center::printCenter() {
  std::cout << "Center : " << this->id << " " << this->name << std::endl;
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      std::cout << "Capacity LSF: ";
    } else {
      std::cout << "Capacity LCP: ";
    }
    for (int j : startingPeriodForPrinting) {
      if (i == 0) {
        std::cout << this->capacity["LSF"][j] << " ";
      } else {
        std::cout << this->capacity["LPC"][j] << " ";
      }
    }
    std::cout << std::endl << "\t";
    for (int j : startingPeriodForPrinting) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Employees LSF: " << this->nbEmployees["LSF"] << std::endl;
  std::cout << "Employees LCP: " << this->nbEmployees["LCP"] << std::endl;
  std::cout << "Lenght of the list of employees : " << this->nbEmployees.size() << std::endl;
  std::cout << "Missions LSF: " << this->nbMissions["LSF"] << std::endl;
  std::cout << "Missions LCP: " << this->nbMissions["LCP"] << std::endl;
  std::cout << std::endl;
}

/* --------------------------------- add employee/mission --------------------------------- */

void center::addEmployee(employee *employee) {
  std::cout << "Add employee " << employee->getSkill() << " " << employee->getId();
  std::cout << " to center " << this->id << std::endl;
  this->employees[employee->getSkill()].push_back(employee);
  //this->nbEmployees[employee->getSkill()] = this->nbEmployees[employee->getSkill()];
  //std::cout << "Size of the list of employees : " << this->nbEmployees[employee->getSkill()]  << std::endl;
}


void center::addMission(mission *mission) {
  this->missions[mission->getSkill()].push_back(mission);
  this->nbMissions[mission->getSkill()]++;
  this->capacity[mission->getSkill()][mission->getStartingPeriod()]--;
}


void center::computeCapacity(std::vector<mission *> mission) {
  if (this->startingPeriodForPrinting.begin() == this->startingPeriodForPrinting.end()) {
    for (auto & m : mission) {
      this->startingPeriodForPrinting.push_back(m->getStartingPeriod());
    }
    this->orderStartingPeriodForPrinting();
  }
  for (auto & m : mission) {
    this->capacity[m->getSkill()][m->getStartingPeriod()] = this->nbEmployees[m->getSkill()];
  }
}

void center::orderStartingPeriodForPrinting() {
  // https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector

  std::set<int> s;
  unsigned size = this->startingPeriodForPrinting.size();
  for (unsigned i = 0; i < size; i++) {
    s.insert(this->startingPeriodForPrinting[i]);
  }
  this->startingPeriodForPrinting.assign(s.begin(), s.end());
}
