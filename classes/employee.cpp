//
// Created by jules on 01/06/2023.
//

#include "employee.hpp"

employee::employee() {
  this->id = 0;
  this->idCenter = 0;
  this->skill = "";
  this->speciality = "";
}

employee::employee(int id, int idCenter, std::string skill, std::string speciality) {
  this->id = id;
  this->idCenter = idCenter;
  this->skill = skill;
  this->speciality = speciality;
}

employee::~employee() = default;

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

void employee::printEmployee() {
  std::cout << this->getId() << " " << this->getIdCenter() << " " << this->getSkill() << " " << this->getSpeciality() << std::endl;
}