/**
 * @file data.cpp
 * @brief Source file for the data class
 * @date 01/06/2023
 *
 * Source file containing the definitions of the methods of the data class
 */

#include "data.hpp"

data::data() = default;

void data::printData() {

  std::cout << "------------------------- Center -------------------------" << std::endl << std::endl;
  std::cout << "nbCenters: " << this->nbCenters << std::endl;
  for (int i = 0; i < this->nbCenters; i++) {
    this->centers[i]->printCenter();
  }

  std::cout << std::endl << "------------------------- Employee -------------------------" << std::endl << std::endl;
  std::cout << "nbEmployees: " << this->nbEmployees << std::endl;
  for (int i = 0; i < this->nbEmployees; i++) {
    this->employees[i]->printEmployee();
  }

  std::cout << std::endl << "------------------------- Mission -------------------------" << std::endl << std::endl;
  std::cout << "nbMissions: " << this->nbMissions << std::endl;
  for (int i = 0; i < this->nbMissions; i++) {
    this->missions[i]->printMission();
  }

  std::cout << std::endl << "------------------------- Distance Matrix -------------------------" << std::endl
            << std::endl;
  this->distancesMatrix->printMatrix();
  std::cout << std::endl << "--------------------------------------------------------------------" << std::endl
            << std::endl << std::endl;

}