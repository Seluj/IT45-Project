//
// Created by jules on 01/06/2023.
//

#include "mission.h"

mission::mission() {
  this->id = 0;
  this->day = 0;
  this->startingPeriod = 0;
  this->endingPeriod = 0;
  this->skill = "";
  this->speciality = "";
}

mission::mission(int id, int day, int startingPeriod, int endingPeriod, std::string skill, std::string speciality) {
  this->id = id;
  this->day = day;
  this->startingPeriod = startingPeriod;
  this->endingPeriod = endingPeriod;
  this->skill = skill;
  this->speciality = speciality;
}

mission::~mission() = default;

int mission::getId() {
  return this->id;
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

std::string mission::getSkill() {
  return this->skill;
}

std::string mission::getSpeciality() {
  return this->speciality;
}

void mission::printMission() {
  std::cout << this->getId() << " " << this->getDay() << " " << this->getStartingPeriod() << " " << this->getEndingPeriod() << " " << this->getSkill() << " " << this->getSpeciality() << std::endl;
}