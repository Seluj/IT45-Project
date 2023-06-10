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
  capacity.clear();
  startingPeriodForPrinting.clear();
}

center::center(int id, std::string name) {
  this->id = id;
  this->name = name;
  capacity.clear();
  startingPeriodForPrinting.clear();
}

/* --------------------------------- Setters --------------------------------- */

void center::updateCapacity(std::string skill, int day, int time){
  this->capacity[skill][day][time] = this->capacity[skill][day][time] - 1;
}

void center::updateCapacity(std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> newCapacity){
    this->capacity = newCapacity;
}

void center::updateMissions(std::unordered_map<std::string, std::vector<mission *>> newMissions){
    this->missions = std::move(newMissions);
    this->nbMissions["LSF"] = this->missions["LSF"].size();
    this->nbMissions["LPC"] = this->missions["LPC"].size();
}

/* --------------------------------- Destructor --------------------------------- */

center::~center() = default;

/* --------------------------------- Getters --------------------------------- */

int center::getCapacity(const std::string& skill, int day, const int time) {
  return this->capacity[skill][day][time];
}

std::unordered_map<std::string, std::vector<std::unordered_map<int, int>>> center::getCapacity() {
    return this->capacity;
}

int center::getNbEmployees(const std::string& skill) {
  return this->nbEmployees[skill];
}

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
    for (int k = 0; k < 5; k++) {
      std::cout << "Day " << k << "\t";
      for (int j : startingPeriodForPrinting) {
        std::cout << this->capacity[i.first][k][j] << "\t";
      }
      std::cout << std::endl;
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
  this->capacity[mission->getSkill()][mission->getDay() - 1][mission->getStartingPeriod()]--;
}


void center::computeCapacity(std::vector<mission *> mission) {
  if (this->startingPeriodForPrinting.begin() == this->startingPeriodForPrinting.end()) {
    for (auto & m : mission) {
      this->startingPeriodForPrinting.push_back(m->getStartingPeriod());
    }
    this->orderStartingPeriodForPrinting();
  }
  for (auto & m : mission) {
    if (this->capacity[m->getSkill()].empty())
      this->capacity[m->getSkill()].resize(5);
    this->capacity[m->getSkill()][m->getDay() - 1][m->getStartingPeriod()] = this->nbEmployees[m->getSkill()];
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
