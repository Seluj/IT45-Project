/**
 * @file employee.cpp
 * @brief Source file for class employee
 * @date 02/06/2023
 *
 * All the methods of the class employee are here
 */

#include "employee.hpp"

#include <utility>

/* --------------------------------- Constructor --------------------------------- */

employee::employee() {
  this->id = 0;
  this->idCenter = 0;
  this->skill = "";
  this->speciality = "";
  this->missions = {};
}

employee::employee(int id, int idCenter, std::string skill, std::string speciality) {
  this->id = id;
  this->idCenter = idCenter;
  this->missions = {};

  // Move the string instead of copying it (more efficient)
  this->skill = std::move(skill);
  this->speciality = std::move(speciality);
}

/* --------------------------------- Destructor --------------------------------- */

employee::~employee() = default;

/* --------------------------------- accessors --------------------------------- */

int employee::getId() {
  return this->id;
}

int employee::getIdCenter() {
  return this->idCenter;
}

std::string employee::getSkill() {
  return this->skill;
}

std::string employee::getSpeciality() {
  return this->speciality;
}

std::vector<int> employee::getMissions() {
  return this->missions;
}



void employee::addMission(int idMission) {
  this->missions.push_back(idMission);
}

void employee::removeMission(int idMission) {
  for (int i = 0; i < this->missions.size(); i++) {
    if (this->missions[i] == idMission) {
      this->missions.erase(this->missions.begin() + i);
    }
  }
}

/* --------------------------------- Print Method --------------------------------- */

void employee::printEmployee() {
  std::cout << this->getId() << " " << this->getIdCenter() << " " << this->getSkill() << " " << this->getSpeciality() << std::endl;
}