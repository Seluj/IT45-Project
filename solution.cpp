//
// Created by jules on 08/06/2023.
//

#include "solution.hpp"

solution::solution(data *data) {
  this->z = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        this->affectations[data->employees[i]->getSkill()][i][j] = 0;
      }
    }
  }
}

//this->z += data->distancesMatrix->getDistance(data->employees[i]->getIdCenter(), data->missions[j]->getIdCenter());

solution::solution() {

}

solution::~solution() = default;

void solution::printSolution() {
  std::cout << "Solution : " << std::endl;
  std::vector<std::string> skills = {"LSF", "LPC"};

  for (int i = 0; i < skills.size(); i++) {
    std::cout << "Table for skill " << skills[i] << std::endl;
    for (int j = 0; j < correspondanceEmployee[skills[i]].size(); j++) {
      for (int k = 0; k < correspondanceMission[skills[i]].size(); j++) {
        std::cout << affectations[skills[i]][correspondanceEmployee[skills[i]][j]][correspondanceMission[skills[i]][k]] << " ";
      }
    }
  }
}