/**
 * @file dataCollection.cpp
 * @brief Source file for dataCollection.hpp
 * @date 01/06/2023
 *
 * Source file containing the dataCollection class
 */

#include "dataCollection.hpp"

/* ------------------------------ Constructors ----------------------------- */

dataCollection::dataCollection(const std::string &path) {
  this->distance = new distanceCSV(path);
  this->centers = new centersCSV(path);
  this->missions = new missionsCSV(path);
  this->employees = new employeesCSV(path);
}

/* ------------------------------- Destructor ------------------------------ */

dataCollection::~dataCollection() {
  delete this->distance;
  delete this->centers;
  delete this->missions;
  delete this->employees;
}

/* -------------------------------- Getters -------------------------------- */

distanceCSV *dataCollection::getDistance() {
  return this->distance;
}

centersCSV *dataCollection::getCenters() {
  return this->centers;
}

missionsCSV *dataCollection::getMissions() {
  return this->missions;
}

employeesCSV *dataCollection::getEmployees() {
  return this->employees;
}

/* -------------------------------- Print Method -------------------------------- */

void dataCollection::printDataCollection() {
  std::cout << std::endl << "------------------------- Data Collection -------------------------" << std::endl;
  std::cout << "Distance Matrix:" << std::endl;
  this->distance->printMatrix();
  std::cout << "Centers:" << std::endl;
  this->centers->printCenters();
  std::cout << "Missions:" << std::endl;
  this->missions->printMissions();
  std::cout << "Employees:" << std::endl;
  this->employees->printEmployees();
  std::cout << std::endl << "--------------------------------------------------------------------" << std::endl;
}