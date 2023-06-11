/**
 * @file dataAnalysis.cpp
 * @brief Source file for class dataAnalysis
 * @date 01/06/2023
 *
 * Source file containing the definitions of the methods of the dataAnalysis class
 */

#include "dataAnalysis.hpp"


dataAnalysis::dataAnalysis(dataCollection *dataInput, data *dataOutput) {
  // Copy the data about the centers
  dataOutput->centers = dataInput->getCenters()->getCenters();
  dataOutput->nbCenters = dataInput->getCenters()->getNbCenters();

  // Copy the data about the missions
  dataOutput->missions = dataInput->getMissions()->getMissions();
  dataOutput->nbMissions = dataInput->getMissions()->getNbMissions();

  // Copy the data about the employees
  dataOutput->employees = dataInput->getEmployees()->getEmployees();
  dataOutput->nbEmployees = dataInput->getEmployees()->getNbEmployees();

  // Copy the data about the matrix
  dataOutput->distancesMatrix = dataInput->getDistance()->getDistancesMatrix();

  // Add the employees to the centers according to their skills
  for (int i = 0; i < dataOutput->nbEmployees; i++) {
    dataOutput->centers[dataOutput->employees[i]->getIdCenter() - 1]->addEmployee(dataOutput->employees[i]);
  }

  for (int i = 0; i < dataOutput->nbCenters; ++i) {
    dataOutput->centers[i]->computeCapacity(dataOutput->missions);
  }
}

void dataAnalysis::dataAnalysisPrint(data *data1) {

  std::cout << std::endl << "------------------------- Data after analysis -------------------------" << std::endl
            << std::endl;

  data1->printData();

}
