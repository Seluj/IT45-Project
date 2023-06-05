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
  bool info = false;

  std::cout << "Center : " << this->id << " " << this->name << std::endl << std::endl;

  for (auto & i : this->capacity) {
    std::cout << "Capacity " << i.first << " : " << std::endl;
    for (int j : startingPeriodForPrinting) {
      std::cout << j << "\t";
    }
    std::cout << std::endl;
    for (int j : startingPeriodForPrinting) {
      std::cout << this->capacity[i.first][j] << "\t";
    }

    std::cout << std::endl;

    info = true;
  }

  for (auto & i : this->nbEmployees) {
    std::cout << "Employees " << i.first << " : " << i.second << std::endl;

    info = true;
  }
  for (auto & i : this->nbMissions) {
    std::cout << "Missions " << i.first << " : " << i.second << std::endl;

    info = true;
  }

  if (!info) {
    std::cout << "No information" << std::endl;
  }

  std::cout << std::endl;
}

/* --------------------------------- add employee/mission --------------------------------- */

void center::addEmployee(employee *employee) {
  this->employees[employee->getSkill()].push_back(employee);
  this->nbEmployees[employee->getSkill()]++;
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
