/**
 * @file mission.cpp
 * @brief Source file for class mission
 * @date 02/06/2023
 *
 * All the methods of the class mission are here
 */

#include "mission.hpp"

/* --------------------------------- Constructor --------------------------------- */

mission::mission() {
  this->id = 0;
  this->assigned = 0;
  this->day = 0;
  this->startingPeriod = 0;
  this->endingPeriod = 0;
  this->skill = "";
  this->speciality = "";
}

mission::mission(mission *missionToCopy) {
  this->id = missionToCopy->getId();
  this->assigned = missionToCopy->getAssigned();
  this->day = missionToCopy->getDay();
  this->startingPeriod = missionToCopy->getStartingPeriod();
  this->endingPeriod = missionToCopy->getEndingPeriod();
  this->skill = missionToCopy->getSkill();
  this->speciality = missionToCopy->getSpeciality();
}

mission::mission(int id, int day, int startingPeriod, int endingPeriod, std::string skill, std::string speciality) {
  this->id = id;
  this->assigned = 0;
  this->day = day;
  this->startingPeriod = startingPeriod;
  this->endingPeriod = endingPeriod;

  // Move the string instead of copying it (more efficient)
  this->skill = skill;
  this->speciality = speciality;
}

/* --------------------------------- Destructor --------------------------------- */

mission::~mission() = default;

/* --------------------------------- accessors --------------------------------- */

int mission::getId() {
  return this->id;
}

int mission::getAssigned(const std::string &type) {
  if (type == "int") {
    return this->assigned;
  } else {
    if (this->assigned == 0) {
      return false;
    } else {
      return true;
    }
  }
}

int mission::getDay() {
  return this->day;
}

int mission::getStartingPeriod() {
  return this->startingPeriod;
}

int mission::getEndingPeriod() {
  return this->endingPeriod;
}

int mission::getDuration() {
  return this->endingPeriod - this->startingPeriod;
}

std::string mission::getSkill() {
  return this->skill;
}

std::string mission::getSpeciality() {
  return this->speciality;
}

/* --------------------------------- Setters --------------------------------- */

void mission::setAssigned(int assigned) {
  this->assigned = assigned;
}

/* --------------------------------- Print Method --------------------------------- */

void mission::printMission() {
  std::cout << this->getId() << " "
            << this->getDay() << " "
            << this->getStartingPeriod() << " "
            << this->getEndingPeriod() << " "
            << this->getSkill() << " "
            << this->getSpeciality() << " "
            << this->getAssigned()
            << std::endl;
}