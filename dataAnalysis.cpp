/**
 * @file dataAnalysis.cpp
 * @brief Source file for class dataAnalysis
 * @date 01/06/2023
 *
 * Source file containing the definitions of the methods of the dataAnalysis class
 */

#include "dataAnalysis.hpp"


dataAnalysis::dataAnalysis(dataCollection *d, data *data1) {
  // Copy the data about the centers
  data1->centers = d->getCenters()->getCenters();
  data1->nbCenters = d->getCenters()->getNbCenters();

  // Copy the data about the missions
  data1->missions = d->getMissions()->getMissions();
  data1->nbMissions = d->getMissions()->getNbMissions();

  // Copy the data about the matrix
  data1->distancesMatrix = d->getDistance()->getDistancesMatrix();

  // Add the employees to the centers according to their skills
  std::vector<employee *> employees = d->getEmployees()->getEmployees();
  int nbEmployees = d->getEmployees()->getNbEmployees();

  for (int i = 0; i < nbEmployees; i++) {
    if (employees[i]->getSkill() == "LSF") {
      data1->centers[employees[i]->getIdCenter() - 1]->addEmployeeLSF(employees[i]);
    } else if (employees[i]->getSkill() == "LPC") {
      data1->centers[employees[i]->getIdCenter() - 1]->addEmployeeLCP(employees[i]);
    }
  }
}

void dataAnalysis::dataAnalysisPrint(data *data1) {

  std::cout << std::endl << "------------------------- Data after analyse -------------------------" << std::endl << std::endl;

  std::cout << "------------------------- Center -------------------------" << std::endl;
  std::cout << "nbCenters: " << data1->nbCenters << std::endl;
  for (int i = 0; i < data1->nbCenters; i++) {
    data1->centers[i]->printCenter();
  }
  std::cout << std::endl << "------------------------- Mission -------------------------" << std::endl;
  std::cout << "nbMissions: " << data1->nbMissions << std::endl;
  for (int i = 0; i < data1->nbMissions; i++) {
    data1->missions[i]->printMission();
  }
  std::cout << std::endl << "------------------------- Matrix -------------------------" << std::endl;
  data1->distancesMatrix->printMatrix();
  std::cout << std::endl << "--------------------------------------------------------------------" << std::endl;

}
