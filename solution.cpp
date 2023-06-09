//
// Created by jules on 08/06/2023.
//

#include "solution.hpp"

solution::solution(data *data) {
  this->z = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getId()] = false;
      }
    }
  }
}

//this->z += data->distancesMatrix->getDistance(data->employees[i]->getIdCenter(), data->missions[j]->getIdCenter());

solution::solution() {

}

solution::~solution() = default;

void solution::printSolution(data *data) {
  std::cout << std::endl << "------------------------- Solution : ------------------------- " << std::endl;
  std::vector<std::string> skills = {"LSF", "LPC"};

  std::cout << "Size of the affectations table : " << affectations.size() << std::endl;
  std::cout << "Size of the affectations table for LSF : " << affectations["LSF"].size() << std::endl;
  std::cout << "Size of the affectations table for LSF and an employee : " << affectations["LSF"][1].size() << std::endl;
  std::cout << "Size of the affectations table for LPC : " << affectations["LPC"].size() << std::endl;
  std::cout << "Size of the affectations table for LPC and an employee : " << affectations["LPC"][2].size() << std::endl;

  for (const auto & skill : skills) {
    std::cout << "Table for skill : " << skill << std::endl;
    for (int j = 0; j < data->nbEmployees; j++) {
      if (data->employees[j]->getSkill() == skill) {
        std::cout << "Employee " << data->employees[j]->getId() << " : ";
        for (int k = 0; k < data->nbMissions; k++) {
          if (data->employees[j]->getSkill() == data->missions[k]->getSkill())
            std::cout << affectations[skill][data->employees[j]->getId()][data->missions[k]->getId()] << " ";
        }
        std::cout << std::endl;
      }
    }
  }
}