/**
 * @file solution.cpp
 * @brief Source file for solution.hpp
 * @date 08/06/2023
 * 
 * Source file containing the solution class
*/

#include "solution.hpp"

solution::solution(data *data) {

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].empty())
          this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()].resize(5);
        this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()-1][data->missions[j]->getId()] = false;
      }
    }
  }
}


solution::solution() {

}

solution solution::initialSolution(data *data1){
  solution initialSolution;
  std::vector<std::string> skills = {"LSF", "LPC"};
  for (int d = 0; d < 5; d++) { //Iterate over each day
    for (int c = 0; c < data1->nbCenters; c++) { //Iterate over each center
      for (int s = 0; s < 2; s++) { //Iterate over each skill
        for (int e = 0; e < data1->centers[c]->getNbEmployees(skills[s]); e++) { //Iterate over each employee
          for (int m = 0; m < data1->centers[c]->getNbMissions(skills[s]); m++) { //Iterate over each mission
            
          }
          
        }
        
      }
      
    }
    
  }
  return initialSolution;
}

solution::~solution() = default;


void solution::printSolution(data *data) {
  std::cout << std::endl << "------------------------- Solution : ------------------------- " << std::endl;
  std::vector<std::string> skills = {"LSF", "LPC"};

  for (const auto & skill : skills) {
    std::cout << "Table for skill : " << skill << std::endl;
    for (int j = 0; j < data->nbEmployees; j++) {
      if (data->employees[j]->getSkill() == skill) {
        std::cout << "Employee " << data->employees[j]->getId() << " : " << std::endl;
        for (int l = 0; l < 5; l++) {
          std::cout << "Day " << l + 1 << " : ";
          for (int k = 0; k < data->nbMissions; k++) {
            if (data->employees[j]->getSkill() == data->missions[k]->getSkill())
              std::cout
                << affectations[skill][data->employees[j]->getId()][l][data->missions[k]->getId()]
                << " ";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
    }
  }
}

solution *solution::compareSolutions(solution *newSolution, data *data) {
  if (this->compareNBAffectations(newSolution, data) == 0) {
    return newSolution;
  } else if (this->compareNBAffectations(newSolution, data) == 1) {
    if (this->compareDistance(newSolution, data) == 0) {
      return newSolution;
    } else if (this->compareDistance(newSolution, data) == 1) {
      if (this->compareNBSpecialists(newSolution, data) == 0) {
        return newSolution;
      }
    }
  }
  return this;
}

int solution::countAffectations(data * data, int i, int k) {
  int nbAffectations = 0;
  for (int j = 0; j < data->nbMissions; j++) {
    if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
      if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[j]->getId()])
        nbAffectations++;
    }
  }
  return nbAffectations;
}

int solution::compareNBAffectations(solution *newSolution, data *data) {
  int nbAffectationsThis = 0;
  int nbAffectationsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int k = 0; k < 5; k++) {
      nbAffectationsThis += this->countAffectations(data, i, k);
      nbAffectationsNew += newSolution->countAffectations(data, i, k);
    }
  }

  if (nbAffectationsThis < nbAffectationsNew)
    return 0;
  else if (nbAffectationsThis == nbAffectationsNew)
    return 1;
  else
    return 2;
}

int solution::compareDistance(solution *newSolution, data *data) {
  int nbAffectations;
  int lastTime = 0, time = 0;
  int lastIdMission = 0, idMission = 0;
  float lengthThis = 0, lengthNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < 5; j++) {
      nbAffectations = this->countAffectations(data, i, j);
      lastTime = time;
      time = INT_MAX;
      lastIdMission = data->employees[i]->getIdCenter();
      for (int k = 0; k < nbAffectations; k++) {
        for (int l = 0; l < data->nbMissions; l++) {
          if (data->employees[i]->getSkill() == data->missions[l]->getSkill()) {
            if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[l]->getId()]) {
              if (data->missions[l]->getStartingPeriod() < time && data->missions[l]->getStartingPeriod() > lastTime) {
                time = data->missions[l]->getStartingPeriod();
                idMission = data->missions[l]->getId();
              }
            }
          }
        }
        lengthThis += data->distancesMatrix->getDistance(lastIdMission, idMission);
        lastIdMission = idMission;
      }
    }
    for (int j = 0; j < 5; j++) {
      nbAffectations = newSolution->countAffectations(data, i, j);
      lastTime = time;
      time = INT_MAX;
      lastIdMission = data->employees[i]->getIdCenter();
      for (int k = 0; k < nbAffectations; k++) {
        for (int l = 0; l < data->nbMissions; l++) {
          if (data->employees[i]->getSkill() == data->missions[l]->getSkill()) {
            if (newSolution->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][k][data->missions[l]->getId()]) {
              if (data->missions[l]->getStartingPeriod() < time && data->missions[l]->getStartingPeriod() > lastTime) {
                time = data->missions[l]->getStartingPeriod();
                idMission = data->missions[l]->getId();
              }
            }
          }
        }
        lengthNew += data->distancesMatrix->getDistance(lastIdMission, idMission);
        lastIdMission = idMission;
      }
    }
  }

  if (lengthThis < lengthNew)
    return 0;
  else if (lengthThis == lengthNew)
    return 1;
  else
    return 2;
}

int solution::compareNBSpecialists(solution *newSolution, data *data) {
  int nbSpecialistsThis = 0;
  int nbSpecialistsNew = 0;

  for (int i = 0; i < data->nbEmployees; i++) {
    for (int j = 0; j < data->nbMissions; j++) {
      if (data->employees[i]->getSkill() == data->missions[j]->getSkill()) {
        if (this->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) {
          if (data->employees[i]->getSpeciality() == data->missions[j]->getSpeciality())
            nbSpecialistsThis++;
        }
        if (newSolution->affectations[data->employees[i]->getSkill()][data->employees[i]->getId()][data->missions[j]->getDay()][data->missions[j]->getId()]) {
          if (data->employees[i]->getSpeciality() == data->missions[j]->getSpeciality())
            nbSpecialistsNew++;
        }
      }
    }
  }

  if (nbSpecialistsThis < nbSpecialistsNew)
    return 0;
  else if (nbSpecialistsThis == nbSpecialistsNew)
    return 1;
  else
    return 2;
}
