//
// Created by jules on 01/06/2023.
//

#include "dataAnalysis.hpp"

dataAnalysis::dataAnalysis(dataCollection *d, data *data1) {
  data1->centers = d->getCenters()->getCenters();
  data1->nbCenters = d->getCenters()->getNbCenters();
  std::cout << std::endl << "Center Done" << std::endl;


  data1->missions = d->getMissions()->getMissions();
  data1->nbMissions = d->getMissions()->getNbMissions();
  std::cout << std::endl << "Mission Done" << std::endl;

  data1->matrix = d->getDistance()->getMatrix();
  data1->nbRows = d->getDistance()->getNbRows();
  data1->nbColumns = d->getDistance()->getNbColumns();
  std::cout << std::endl << "Matrix Done" << std::endl;

  std::vector<employee *> employees = d->getEmployees()->getEmployees();
  int nbEmployees = d->getEmployees()->getNbEmployees();
  std::cout << "nbEmployee :" << nbEmployees << std::endl;
  std::cout << std::endl << "Employee copying done" << std::endl;


  for (int i = 0; i < nbEmployees; i++) {
    if (employees[i]->getSkill() == "LSF") {

      data1->centers[employees[i]->getIdCenter()]->addEmployeeLSF(employees[i]);
    } else if (employees[i]->getSkill() == "LPC") {
      data1->centers[employees[i]->getIdCenter()]->addEmployeeLCP(employees[i]);
    }
  }

  std::cout << std::endl << "Employee Done" << std::endl;

}

void dataAnalysis::dataAnalysisPrint(data *data1) {
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
  std::cout << "nbRows: " << data1->nbRows << std::endl;
  std::cout << "nbColumns: " << data1->nbColumns << std::endl;
  for (int i = 0; i < data1->nbRows; i++) {
    for (int j = 0; j < data1->nbColumns; j++) {
      std::cout << data1->matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

}
